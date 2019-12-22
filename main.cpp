#include "word.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main(int, char**)
{
    std::vector<Word> word_list
    {
        Word("alma", "apple"),
        Word("korte", "pear"),
        Word("barack", "peach"),
        Word("szilva", "plum")
    };

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

    /*ciklus, amíg a word_list hossza > 0 (while loop)
        word kérdésének kiírása (utolsó elem);
        válasz bekérése;
        ha válasz == correct_válasszal, akkor:
            word eltávolítása a listából (vector pop_back)
        vector összekeverése; (random_shuffle) */
}