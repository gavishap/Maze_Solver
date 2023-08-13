#ifndef SIMPLE_MAZE_2D_GENERATOR_H
#define SIMPLE_MAZE_2D_GENERATOR_H

#include <cstdlib>
#include <ctime>
#include "AbstractMaze2dGenerator.h"

class SimpleMaze2dGenerator : public AbstractMaze2dGenerator {
public:
    Maze2d generate(int width, int height) override {
        Maze2d maze(width, height);

        // Randomly initialize the maze with walls
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                maze.setWall(i, j);
            }
        }

        int startX = rand() % width;
        int startY = 0; // Start at the top edge
        int endX = rand() % width;
        int endY = height - 1; // End at the bottom edge

        maze.set_start(startX, startY);

        

        int x = startX;
        int y = startY;

        while (x != endX || y != endY) {
            int move = rand() % 4; // 0 for left, 1 for right, 2 for up, 3 for down
            switch (move) {
            case 0:
                if (x > 0) x--;
                break;
            case 1:
                if (x < width - 1) x++;
                break;
            case 2:
                if (y > 0) y--;
                break;
            case 3:
                if (y < height - 1) y++;
                break;
            }
            maze.setFree(x, y);
        }

        maze.set_end(endX, endY);

        return maze;
    }
};

#endif // SIMPLE_MAZE_2D_GENERATOR_H
