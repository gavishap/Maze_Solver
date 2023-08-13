#include "MazeFileManager.h"

void MazeFileManager::saveMaze(const Maze2d& maze, const std::string& filename) {
    MazeCompression::compressAndSave(maze, filename);
}

Maze2d MazeFileManager::loadMaze(const std::string& filename) {
    return MazeCompression::loadAndDecompress(filename);
}
