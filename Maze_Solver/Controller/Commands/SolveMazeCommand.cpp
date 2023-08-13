#include "SolveMazeCommand.h"

SolveMazeCommand::SolveMazeCommand(CLIView& v, MazeStorage& ms, SolutionStorage& ss)
    : view(v), mazeStorage(ms), solutionStorage(ss) {}

void SolveMazeCommand::execute() {
    // Fetch the maze from the mazeStorage using the mazeName
    Maze2d maze = mazeStorage.getMaze(mazeName);
    std::vector<Position> solutionPath;

    if (algorithm == "BFS") {
        BFS bfs(&maze);
        solutionPath = bfs.search(maze);
    }
    else if (algorithm == "A*") {
        AStar aStar(&maze);
        solutionPath = aStar.search(maze);
    }
    else {
        view.displayMessage("Invalid algorithm specified.");
        return;
    }

    // Convert the solution path from Position to std::pair<int, int> 
    std::vector<std::pair<int, int>> convertedSolution;
    for (const Position& pos : solutionPath) {
        convertedSolution.emplace_back(pos.x, pos.y);
    }
    

    // Store the solution in the solutionStorage
    solutionStorage.addSolution(mazeName, convertedSolution);

    // Notify the user that the maze has been solved
    view.displayMessage("Solution for " + mazeName + " is ready.");
}

void SolveMazeCommand::setDetails(const std::string& name, const std::string& algo) {
    mazeName = name;
    algorithm = algo;
}
