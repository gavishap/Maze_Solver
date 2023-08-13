#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Controller/Commands/Command.h"
#include "../View/CLIView.h"
#include "../Model/MyMaze2dGenerator.h"
#include "../Model/MazeStorage.h"
#include "../Model/SolutionStorage.h"
#include "../Controller/MazeFileManager.h"
#include "../Model/MazeCompression.h"
#include "../Controller/Commands/DisplaySolutionCommand.h"
#include <unordered_map>
#include <memory>

class Controller {
private:
    CLIView view;
    MazeStorage mazeStorage;
    MazeFileManager mazeFileManager;
    SolutionStorage solutionStorage;  
    DisplaySolutionCommand displaySolutionCommand;  
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;

public:
    Controller();
    void executeCommand(const std::string& cmdName);
};

#endif // CONTROLLER_H
