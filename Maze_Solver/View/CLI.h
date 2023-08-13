#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include "../View/CLIView.h"
#include "../Controller/Controller.h"

class CLI {
private:
    CLIView view;
    Controller& controller;

public:
    CLI(std::istream& input, std::ostream& output, Controller& ctrl);
    void start();
};

#endif // CLI_H
