#include "word.h"

#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

std::string filename;
int count = 3;

void print_usage(std::string program_name)
{
    std::cout << "Usage: " << program_name << " -f <filename> [-c <question_count>] [-h]" << std::endl;
    std::cout << "    -f: Name of input file. Each line is 1 question. Format: <question>/<answer>." << std::endl;
    std::cout << "    -c: How many times you want every word to be asked. Default value is 3." << std::endl;
    std::cout << "    -h: Print this message." << std::endl;
}

void parse_options(int argc, char** args)
{
    if (argc == 1)
    {
        print_usage(args[0]);
        exit(0);
    }

    for (int arg_index = 1; arg_index < argc; ++arg_index)
    {
        if (strcmp(args[arg_index], "-h") == 0)
        {
            print_usage(args[0]);
            exit(0);
        }

        if ((strcmp(args[arg_index], "-f") == 0) && (arg_index + 1 != argc))
        {
            filename = args[++arg_index];

            continue;
        }

        if ((strcmp(args[arg_index], "-c") == 0) && (arg_index + 1 != argc))
        {
            count = std::stoi(args[++arg_index]);

            continue;
        }

        std::cout << "Invalid parameter: " << args[arg_index] << std::endl;
        print_usage(args[0]);
        exit(0);
    }
}

std::vector<Word> read_from_file()
{
    std::ifstream file(filename);
    std::vector<Word> word_list;

    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return word_list;
    }

    std::string line;

    while (std::getline(file, line))
    {
        Word new_word(line.substr(0, line.find("/")), line.substr(line.find("/") + 1, std::string::npos));

        for (int i = 0; i < count; ++i)
        {
            word_list.push_back(new_word);
        }
    }
    file.close();

    return word_list;
}

int main(int argc, char** args)
{
    parse_options(argc, args);

    std::vector<Word> word_list = read_from_file();

    const double number_of_original_questions = word_list.size();

    srand(static_cast<unsigned int>(time(NULL)));

    while (!word_list.empty())
    {
        std::random_device rd;
        std::mt19937 g(rd());
 
        std::shuffle(word_list.begin(), word_list.end(), g);
        
        Word& current_question = word_list.back();
        int progress = 100.0 - (static_cast<double>(word_list.size()) / number_of_original_questions * 100.0);

        std::string user_answer;
        std::cout << "[" << progress << "%] " << current_question.question() << ": ";
        std::getline(std::cin, user_answer);

        if (user_answer == current_question.correct_answer())
        {
            word_list.pop_back();
            std::cout << "Correct answer!" << std::endl << std::endl;
        }else
        {
            std::cout << "Incorrect answer! The correct answer was: " << current_question.correct_answer() << std::endl << std::endl;
        }
    }
}