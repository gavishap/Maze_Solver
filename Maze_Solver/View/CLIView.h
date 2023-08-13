#ifndef CLIVIEW_H
#define CLIVIEW_H

#include <iostream>
#include "../Model/Maze2d.h"

class CLIView {
public:
    CLIView(std::istream& input, std::ostream& output);

    void displayMaze(const Maze2d& maze);
    void displayMessage(const std::string& message);
    std::string getUserCommand();

private:
    std::istream& in;
    std::ostream& out;
};

#endif // CLIVIEW_H
