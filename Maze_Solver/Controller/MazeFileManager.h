#ifndef MAZE_FILE_MANAGER_H
#define MAZE_FILE_MANAGER_H

#include "../Model/Maze2d.h"
#include "../Model/MazeCompression.h"
#include <string>

class MazeFileManager {
public:
    // Saves a maze to a file
    static void saveMaze(const Maze2d& maze, const std::string& filename);

    // Loads a maze from a file
    static Maze2d loadMaze(const std::string& filename);
};

#endif // MAZE_FILE_MANAGER_H
