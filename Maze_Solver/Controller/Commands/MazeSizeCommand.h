#ifndef MAZE_SIZE_COMMAND_H
#define MAZE_SIZE_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../../Model/MazeStorage.h"

class MazeSizeCommand : public Command {
private:
    CLIView& view;
    MazeStorage& mazeStorage;
    std::string mazeName;

public:
    MazeSizeCommand(CLIView& v, MazeStorage& ms);
    void execute() override;
    std::string getName() const override { return "maze size"; }
    void setMazeName(const std::string& name);
};

#endif // MAZE_SIZE_COMMAND_H
