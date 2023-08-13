#include "CLI.h"
#include <sstream>

CLI::CLI(std::istream& input, std::ostream& output, Controller& ctrl)
    : view(input, output), controller(ctrl) {}

void CLI::start() {
    view.displayMessage("Welcome to the Maze CLI!");
    view.displayMessage("Type 'help' for a list of commands or 'exit' to quit.");

    std::string userInput;
    while (true) {
        view.displayMessage("> "); // Command prompt
        userInput = view.getUserCommand();

        if (userInput == "exit") {
            view.displayMessage("Exiting Maze CLI. Goodbye!");
            break;
        }
        else if (userInput == "help") {
            view.displayMessage("Available commands:");
            view.displayMessage("generate maze <name> <width> <height> - Generate a new maze with given name and dimensions.");
            view.displayMessage("display <name> - Display a maze with the given name.");
            view.displayMessage("save maze <name> <filename> - Save the maze with the given name to a file.");
            view.displayMessage("load maze <filename> <name> - Load a maze from a file and assign it a name.");
            view.displayMessage("maze size <name> - Get the size of the maze with the given name.");
            view.displayMessage("file size <filename> - Get the size of the file with the given filename.");
            view.displayMessage("solve <name> <algorithm> - Solve the maze with the given name using the specified algorithm (e.g., BFS, A*).");
            view.displayMessage("display solution <name> - Display the solution for the maze with the given name.");
            view.displayMessage("dir <path> - List contents of the directory.");
            view.displayMessage("exit - Exit the program.");
        }
        else {
            controller.executeCommand(userInput);
        }
    }
}
