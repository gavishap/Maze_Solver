#ifndef ABSTRACT_MAZE_2D_GENERATOR_H
#define ABSTRACT_MAZE_2D_GENERATOR_H
#include <string>
#include <chrono>
#include "Maze2dGenerator.h"
class AbstractMaze2dGenerator : public Maze2dGenerator {
public:
    virtual Maze2d generate(int width, int height) = 0;

    std::string measureAlgorithmTime(int width, int height) override {
        auto start = std::chrono::high_resolution_clock::now();
        generate(width, height);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        return "Time taken: " + std::to_string(duration.count()) + " ms";
    }

    virtual ~AbstractMaze2dGenerator() {}
};
#endif // ABSTRACT_MAZE_2D_GENERATOR_H 