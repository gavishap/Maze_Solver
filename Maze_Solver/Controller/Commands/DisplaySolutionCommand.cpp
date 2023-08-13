#include "DisplaySolutionCommand.h"
#include <sstream>
#include <vector>
#include <utility> 
#include "../../View/CLIView.h"
#include "../../Model/SolutionStorage.h"

DisplaySolutionCommand::DisplaySolutionCommand(CLIView& v, SolutionStorage& ss)
    : view(v), solutionStorage(ss) {}


void DisplaySolutionCommand::setMazeName(const std::string& name) {
    mazeName = name;
}

void DisplaySolutionCommand::execute() {
    if (solutionStorage.solutionExists(mazeName)) {
        std::vector<std::pair<int, int>> solution = solutionStorage.getSolution(mazeName);

        // Convert solution to a readable format
        std::stringstream ss;
        ss << "Solution for maze " << mazeName << ":\n";
        for (size_t i = 0; i < solution.size(); i++) {
            ss << "(" << solution[i].first << ", " << solution[i].second << ")";
            if (i != solution.size() - 1) {
                ss << " -> ";
            }
        }
        ss << "\nEnd of solution.";

        view.displayMessage(ss.str());
    }
    else {
        view.displayMessage("No solution found for the maze named: " + mazeName);
    }
}
