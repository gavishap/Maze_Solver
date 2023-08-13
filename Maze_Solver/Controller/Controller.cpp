#include "../Controller/Controller.h"
#include "../Controller/Commands/DirCommand.h" 
#include "../Controller/Commands/GenerateMazeCommand.h"
#include "../Controller/Commands/DisplayCommand.h"
#include "../Controller/Commands/SaveMazeCommand.h"
#include "../Controller/Commands/LoadMazeCommand.h"
#include "../Controller/Commands/MazeSizeCommand.h"
#include "../Controller/Commands/FileSizeCommand.h"
#include "../Controller/Commands/SolveMazeCommand.h"

#include <sstream>
Controller::Controller() : view(std::cin, std::cout),
mazeStorage(),
mazeFileManager(),
solutionStorage(),
displaySolutionCommand(view, solutionStorage),
commands() {
    commands["dir"] = std::make_unique<DirCommand>(view, mazeStorage);
    commands["generate maze"] = std::make_unique<GenerateMazeCommand>(view, mazeStorage);
    commands["display"] = std::make_unique<DisplayCommand>(view, mazeStorage);
    commands["save maze"] = std::make_unique<SaveMazeCommand>(view, mazeStorage, mazeFileManager); 
    commands["load maze"] = std::make_unique<LoadMazeCommand>(view, mazeStorage, mazeFileManager);
    commands["maze size"] = std::make_unique<MazeSizeCommand>(view, mazeStorage);
    commands["file size"] = std::make_unique<FileSizeCommand>(view, mazeFileManager);
    commands["solve"] = std::make_unique<SolveMazeCommand>(view, mazeStorage, solutionStorage); 
    commands["display solution"] = std::make_unique<DisplaySolutionCommand>(view, solutionStorage);
     // Load all solutions from files at startup
    solutionStorage.loadAllSolutions();
}


void Controller::executeCommand(const std::string& fullCommand) {
    std::istringstream iss(fullCommand);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        return;
    }

    std::string cmd = tokens[0];
    if (tokens.size() > 1) {
        if (cmd == "generate" && tokens[1] == "maze") {
            cmd += " " + tokens[1];
            if (tokens.size() >= 5) {
                std::string name = tokens[2];
                int w = std::stoi(tokens[3]);
                int h = std::stoi(tokens[4]);
                auto genCmd = dynamic_cast<GenerateMazeCommand*>(commands[cmd].get());
                if (genCmd) {
                    genCmd->setMazeDetails(name, w, h);
                }
            }
            else {
                view.displayMessage("Invalid command format: Expected 'generate maze <name> <width> <height>'");
                return;
            }
        }
        else if (cmd == "display") {
            if (tokens[1] != "solution") {
                auto dispCmd = dynamic_cast<DisplayCommand*>(commands[cmd].get());
                if (dispCmd) {
                    dispCmd->setMazeName(tokens[1]);
                }
            }
            else {
                cmd += " " + tokens[1];
                if (tokens.size() >= 3) {
                    dynamic_cast<DisplaySolutionCommand*>(commands[cmd].get())->setMazeName(tokens[2]);
                }
            }
        }
        else if (cmd == "save" && tokens[1] == "maze") {
            cmd += " " + tokens[1];
            if (tokens.size() >= 4) {
                std::string name = tokens[2];
                std::string path = tokens[3];
                auto saveCmd = dynamic_cast<SaveMazeCommand*>(commands[cmd].get());
                if (saveCmd) {
                    saveCmd->setDetails(name, path);
                }
            }
        }
        else if (cmd == "load" && tokens[1] == "maze") {
            cmd += " " + tokens[1];
            if (tokens.size() >= 3) {
                dynamic_cast<LoadMazeCommand*>(commands[cmd].get())->setDetails(tokens[2]);
            }
        }
        else if (cmd == "maze" && tokens[1] == "size") {
            cmd += " " + tokens[1];
            if (tokens.size() >= 3) {
                dynamic_cast<MazeSizeCommand*>(commands[cmd].get())->setMazeName(tokens[2]);
            }
        }
        else if (cmd == "file" && tokens[1] == "size") {
            cmd += " " + tokens[1];
            if (tokens.size() >= 3) {
                dynamic_cast<FileSizeCommand*>(commands[cmd].get())->setFileName(tokens[2]);
            }
        }
        else if (cmd == "solve") {
            if (tokens.size() >= 3) {
                std::string name = tokens[1];
                std::string algo = tokens[2];

                // Get the maze by name
                Maze2d maze = mazeStorage.getMaze(name);

                // Generate the solution
                auto solveCmd = dynamic_cast<SolveMazeCommand*>(commands[cmd].get());
                solveCmd->setDetails(name, algo);
                solveCmd->execute();

                // Now retrieve the solution from SolutionStorage
                std::vector<std::pair<int, int>> pairs = solutionStorage.getSolution(name);
                std::cout << "Retrieved solution from storage with size: " << pairs.size() << std::endl;

                std::vector<Position> solutionPath;
                for (const auto& p : pairs) {
                    solutionPath.push_back(Position(p.first, p.second));
                }
                for (const auto& pos : solutionPath) {
                    std::cout << "(" << pos.x << ", " << pos.y << ")" << "->";
                }

                // Mark the maze with the solution path
                for (const Position& position : solutionPath) {
                    maze.markPosition(position);
                }

                // Display the solved maze
                std::cout << "Solved Maze:" << std::endl;
                std::cout << maze << std::endl;

                // Save the solution to a file
                solutionStorage.saveSolutionToFile(name);
            }
        }




        else if (cmd == "dir") {
            if (tokens.size() >= 2) {
                auto dirCmd = dynamic_cast<DirCommand*>(commands[cmd].get());
                if (dirCmd) {
                    dirCmd->setPath(tokens[1]);
                }
            }
        }
    }

    // Execute the command if it exists
    if (commands.find(cmd) != commands.end()) {
        commands[cmd]->execute();
    }
    else {
        view.displayMessage("Invalid command: " + cmd);
    }
}

