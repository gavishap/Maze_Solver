#include "CLIView.h"
#include <string>

CLIView::CLIView(std::istream& input, std::ostream& output) : in(input), out(output) {}

void CLIView::displayMaze(const Maze2d& maze) {
    out << maze << std::endl;
}

void CLIView::displayMessage(const std::string& message) {
    out << message << std::endl;
}

std::string CLIView::getUserCommand() {
    std::string cmd;
    std::getline(in, cmd);
    return cmd;
}
