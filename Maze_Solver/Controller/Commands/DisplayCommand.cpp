#include "DisplayCommand.h"

void DisplayCommand::execute() {
    if (mazeName.empty()) {
        view.displayMessage("Error: Maze name not specified!");
        return;
    }

    if (!mazeStorage.mazeExists(mazeName)) {
        view.displayMessage("Maze with name " + mazeName + " does not exist.");
        return;
    }

    const Maze2d& maze = mazeStorage.getMaze(mazeName); 
    view.displayMaze(maze);
}
