#ifndef GENERATE_MAZE_COMMAND_H
#define GENERATE_MAZE_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../../Model/MazeStorage.h"
#include <string>

class GenerateMazeCommand : public Command {
private:
    CLIView& view;
    MazeStorage& mazeStorage;
    std::string mazeName;
    int width;
    int height;

public:
    GenerateMazeCommand(CLIView& v, MazeStorage& ms)
        : view(v), mazeStorage(ms), width(0), height(0) {}

    void execute() override;
    std::string getName() const override { return "generate maze"; }
    void setMazeDetails(const std::string& name, int w, int h) {
        mazeName = name;
        width = w;
        height = h;
    }
};

#endif // GENERATE_MAZE_COMMAND_H
