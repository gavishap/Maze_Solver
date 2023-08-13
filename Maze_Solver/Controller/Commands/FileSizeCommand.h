#ifndef FILE_SIZE_COMMAND_H
#define FILE_SIZE_COMMAND_H

#include "Command.h"
#include "../../View/CLIView.h"
#include "../MazeFileManager.h"

class FileSizeCommand : public Command {
private:
    CLIView& view;
    MazeFileManager& mazeFileManager;
    std::string filename;

public:
    FileSizeCommand(CLIView& v, MazeFileManager& mfm);

    void execute() override;
    std::string getName() const override { return "file size"; }

    void setFileName(const std::string& name);
};

#endif // FILE_SIZE_COMMAND_H

