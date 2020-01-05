#include "word.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>



std::vector<Word> read_from_file(const std::string& filename)
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

        word_list.push_back(new_word);
    }
    file.close();

    return word_list;
}

int main(int argc, char** args)
{
    std::vector<Word> word_list = read_from_file("words.txt");

    const double number_of_original_questions = word_list.size();

    while (!word_list.empty())
    {
        std::random_device rd;
        std::mt19937 g(rd());
 
        std::shuffle(word_list.begin(), word_list.end(), g);
        
        Word& current_question = word_list.back();
        double progress = 100.0 - (static_cast<double>(word_list.size()) / number_of_original_questions * 100.0);

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