#ifndef MY_MAZE_2D_GENERATOR_H
#define MY_MAZE_2D_GENERATOR_H
#include <stack>
#include <ctime>
#include <cstdlib>
#include <random>
#include "AbstractMaze2dGenerator.h"
class MyMaze2dGenerator : public AbstractMaze2dGenerator {
private:
    // Directions to move
    std::vector<std::pair<int, int>> directions = {
        {0, 2},
        {2, 0},
        {0, -2},
        {-2, 0}
    };

    // Check if cell is within maze bounds
    bool inBounds(int x, int y, int width, int height) {
        return x >= 0 && x < width&& y >= 0 && y < height;
    }

public:
    void setStartAndEndWithOpenNeighbor(Maze2d& maze, int width, int height) {
        int startX, startY = 0, endX, endY = height - 1;

        // Set random starting point on the top row and ensure it has an open neighbor
        do {
            startX = rand() % width;
        } while (maze.getPossibleMoves({ startX, startY }).empty());
        maze.set_start(startX, startY);

        // Set random ending point and ensure it's not the starting point
        do {
            endX = rand() % width;
            //endY = rand() % height;
        } while (startX == endX && startY == endY);
        maze.set_end(endX, endY);
    }

    Maze2d generate(int width, int height) override {
        Maze2d maze(width, height);

        // Ensure dimensions are odd for the algorithm to work effectively
        if (width % 2 == 0) width--;
        if (height % 2 == 0) height--;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                maze.setWall(i, j);
            }
        }

        std::stack<std::pair<int, int>> stack;
        int startX = rand() % width;
        int startY = rand() % height;

        // Ensure starting point is odd to fit the algorithm's requirements
        while (startX % 2 == 0) startX = (startX + 1) % width;
        while (startY % 2 == 0) startY = (startY + 1) % height;


        stack.push({ startX, startY });
        maze.setFree(startX, startY);

        while (!stack.empty()) {
            int x = stack.top().first;
            int y = stack.top().second;
            stack.pop();

            // Shuffle directions for randomness
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(directions.begin(), directions.end(), g);

            for (auto dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;

                if (inBounds(newX, newY, width, height) && maze.is_wall(newX, newY)) {
                    int betweenX = (x + newX) / 2;
                    int betweenY = (y + newY) / 2;

                    maze.setFree(betweenX, betweenY);
                    maze.setFree(newX, newY);

                    stack.push({ newX, newY });
                }
            }
        }


        // Set random start and end points
        setStartAndEndWithOpenNeighbor(maze, width, height);

        return maze;
    }
};
#endif // MY_MAZE_2D_GENERATOR_H