#ifndef DIR_COMMAND_H
#define DIR_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../../Model/MazeStorage.h"

class DirCommand : public Command {
private:
    CLIView& view;
    MazeStorage& mazeStorage;
    std::string dirPath; 

public:
    DirCommand(CLIView& v, MazeStorage& ms) : view(v), mazeStorage(ms) {}
    void execute() override;
    std::string getName() const override { return "dir"; }

    void setPath(const std::string& path) { dirPath = path; }  
};

#endif // DIR_COMMAND_H
