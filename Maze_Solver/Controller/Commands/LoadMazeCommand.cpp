#include "LoadMazeCommand.h"
#include <filesystem>
LoadMazeCommand::LoadMazeCommand(CLIView& v, MazeStorage& ms, MazeFileManager& mfm)
    : view(v), mazeStorage(ms), mazeFileManager(mfm) {}

void LoadMazeCommand::setDetails(const std::string& filePath) {
    path = filePath;
}

void LoadMazeCommand::execute() {
    if (path.empty()) {
        view.displayMessage("Error: No path specified for loading the maze.");
        return;
    }

    try {
        Maze2d loadedMaze = MazeFileManager::loadMaze(path);

       
        std::filesystem::path p(path);
        std::string mazeName = p.stem().string();

        mazeStorage.addMaze(mazeName, loadedMaze);
        view.displayMessage("Maze successfully loaded from: " + path);
    }
    catch (const std::exception& e) {
        view.displayMessage("Error loading maze from '" + path + "': " + e.what());
    }
}
