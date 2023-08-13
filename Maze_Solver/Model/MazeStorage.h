#ifndef MAZESTORAGE_H
#define MAZESTORAGE_H

#include "Maze2d.h"
#include <unordered_map>
#include <string>

class MazeStorage {
private:
    std::unordered_map<std::string, Maze2d> mazes; // Stores mazes by their name

public:
    // Adds a maze to storage
    void addMaze(const std::string& name, const Maze2d& maze);

    // Retrieves a maze by its name
    Maze2d getMaze(const std::string& name);

    // Checks if a maze with the given name exists in storage
    bool mazeExists(const std::string& name);

};

#endif // MAZESTORAGE_H
