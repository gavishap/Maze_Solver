#include "MazeSizeCommand.h"
#include <sstream>

MazeSizeCommand::MazeSizeCommand(CLIView& v, MazeStorage& ms)
    : view(v), mazeStorage(ms) {}


void MazeSizeCommand::setMazeName(const std::string& name) {
    mazeName = name;
}

void MazeSizeCommand::execute() {
    // Ensure the maze exists
    if (!mazeStorage.mazeExists(mazeName)) {
        view.displayMessage("Error: Maze with name " + mazeName + " does not exist.");
        return;
    }

    const Maze2d& maze = mazeStorage.getMaze(mazeName);

    int width = maze.getWidth();
    int height = maze.getHeight();

    std::stringstream ss;
    ss << "Size of maze '" << mazeName << "': " << width << "x" << height;
    view.displayMessage(ss.str());
}

