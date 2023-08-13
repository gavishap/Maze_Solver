#ifndef LOAD_MAZE_COMMAND_H
#define LOAD_MAZE_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../../Model/MazeStorage.h"
#include "../MazeFileManager.h"

class LoadMazeCommand : public Command {
private:
    CLIView& view;
    MazeStorage& mazeStorage;
    MazeFileManager& mazeFileManager;
    std::string path;

public:
    LoadMazeCommand(CLIView& v, MazeStorage& ms, MazeFileManager& mfm);

    void execute() override;

    std::string getName() const override { return "load maze"; }

    // A method to set the path from which the maze will be loaded
    void setDetails(const std::string& filePath);
};

#endif // LOAD_MAZE_COMMAND_H
