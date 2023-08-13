#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
    virtual ~Command() = default;

    // The primary action of the command
    virtual void execute() = 0;

    // Retrieve the name of the command
    virtual std::string getName() const = 0;
};

#endif // COMMAND_H
