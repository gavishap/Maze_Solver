#include "MazeStorage.h"

void MazeStorage::addMaze(const std::string& name, const Maze2d& maze) {
    mazes[name] = maze;
}

Maze2d MazeStorage::getMaze(const std::string& name) {
    if (mazeExists(name)) {
        return mazes[name];
    }

    return Maze2d(0, 0);
}

bool MazeStorage::mazeExists(const std::string& name) {
    return mazes.find(name) != mazes.end();
}
