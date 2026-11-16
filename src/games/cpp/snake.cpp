#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "snake.h"


// This sets the playfield dimensions by X and Y
constexpr int x_max = 100;
constexpr int y_max = 25;
constexpr int max_snake_length = 100;

bool gameOver;
int x;
int y;
int fruitX;
int fruitY;
int score;


// Store each segment's coordinates; nSnake tracks the current number of segments.
int snakeX[max_snake_length];
int snakeY[max_snake_length];
int nSnake;

std::string fruit = "*";

enum Directions
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

Directions dir;

static void setup()
{
    // The purpose of seeding the random number generator because the * is supposed to appear randomly on the board
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // active
    gameOver = false;
    // dir = stop is what calls the enum value for when the snake wants to stop
    dir = STOP;
    // Set the snake's starting position near the center of the board.
    x = x_max / 2;
    y = y_max / 2;
    // What it is you are supposed to do with this code is have the * at random coordinates
    fruitX = std::rand() % x_max;
    fruitY = std::rand() % y_max;
    // score = 0 is when its counting from 0
    score = 0;
    // What these do is it helps initalize the snake so it can move
    nSnake = 1;
    snakeX[0] = x;
    snakeY[0] = y;
}

void run_snake()
{
    setup();
    std::cout << "Snake initialized. The game loop is not implemented yet.\n";
}
