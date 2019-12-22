#ifndef WORD_H
#define WORD_H

#include <string>

class Word
{
public:
    Word(std::string question, std::string correct_answer);

    std::string question() const;
    std::string correct_answer() const;

private:
    std::string question_;
    std::string correct_answer_;
};

#endif