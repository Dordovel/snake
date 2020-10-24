#ifndef SNAKE
#define SNAKE

#include <vector>
#include "./object.h"

struct Snake
{
    Object head;
    std::vector<Object> tails;
};

#endif //SNAKE