#ifndef SAVE_MAZE_COMMAND_H
#define SAVE_MAZE_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../../Model/MazeStorage.h"
#include "../MazeFileManager.h"
#include <string>

class SaveMazeCommand : public Command {
private:
    CLIView& view;
    MazeStorage& mazeStorage;
    MazeFileManager& mazeFileManager;
    std::string mazeName;     // Name of the maze to save
    std::string filePath;     // Path to save the maze

public:
    SaveMazeCommand(CLIView& v, MazeStorage& ms, MazeFileManager& mfm);
    void setDetails(const std::string& mazeName, const std::string& path);  // To set maze name and path details before execution
    void execute() override;
    std::string getName() const override { return "save maze"; }
};

#endif // SAVE_MAZE_COMMAND_H
