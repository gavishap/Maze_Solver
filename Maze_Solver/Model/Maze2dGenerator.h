#ifndef MAZE_2D_GENERATOR_H
#define MAZE_2D_GENERATOR_H

#include "Maze2d.h"

class Maze2dGenerator {
public:
    virtual Maze2d generate(int width, int height) = 0;
    virtual std::string measureAlgorithmTime(int width, int height) = 0;
    virtual ~Maze2dGenerator() {}
};

#endif // MAZE_2D_GENERATOR_H