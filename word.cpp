#include "word.h"

Word::Word(std::string question, std::string correct_answer)
    : question_(question),
      correct_answer_(correct_answer)
{

}

std::string Word::question() const
{
    return question_;
}

std::string Word::correct_answer() const
{
    return correct_answer_;
}