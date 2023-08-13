#include "SaveMazeCommand.h"

SaveMazeCommand::SaveMazeCommand(CLIView& v, MazeStorage& ms, MazeFileManager& mfm)
    : view(v), mazeStorage(ms), mazeFileManager(mfm) {}

void SaveMazeCommand::setDetails(const std::string& mazeName, const std::string& path) {
    this->mazeName = mazeName;
    this->filePath = path;
}

void SaveMazeCommand::execute() {
    // Check if the maze with the specified name exists
    if (!mazeStorage.mazeExists(mazeName)) {
        view.displayMessage("Error: Maze with name " + mazeName + " does not exist.");
        return;
    }

    // Fetch the maze from the mazeStorage
    const Maze2d& mazeToSave = mazeStorage.getMaze(mazeName);

    // Save the maze to the file
    try {
        MazeFileManager::saveMaze(mazeToSave, filePath);
        view.displayMessage("Maze saved successfully to " + filePath);
    }
    catch (const std::exception& e) {
        view.displayMessage("Error saving maze: " + std::string(e.what()));
    }
}


