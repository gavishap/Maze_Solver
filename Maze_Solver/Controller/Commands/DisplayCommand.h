#ifndef DISPLAY_COMMAND_H
#define DISPLAY_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../../Model/MazeStorage.h"
#include <string>

class DisplayCommand : public Command {
private:
    CLIView& view;
    MazeStorage& mazeStorage;
    std::string mazeName;

public:
    DisplayCommand(CLIView& v, MazeStorage& ms)
        : view(v), mazeStorage(ms) {}

    void execute() override;
    std::string getName() const override { return "display"; }

    // Setter to specify which maze to display
    void setMazeName(const std::string& name) {
        mazeName = name;
    }
};

#endif // DISPLAY_COMMAND_H
