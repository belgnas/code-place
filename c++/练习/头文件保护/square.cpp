#include "square.h"

int getSquareSides() // 实际定义 getSquareSides
{
    return 4;
}

int getSquarePerimeter(int sideLength)
{
    return sideLength * getSquareSides();
}