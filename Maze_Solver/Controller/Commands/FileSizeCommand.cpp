#include "FileSizeCommand.h"
#include <filesystem>

FileSizeCommand::FileSizeCommand(CLIView& v, MazeFileManager& mfm)
    : view(v), mazeFileManager(mfm) {}

void FileSizeCommand::execute() {
    try {
        std::uintmax_t size = std::filesystem::file_size(filename);
        view.displayMessage("File size of " + filename + ": " + std::to_string(size) + " bytes");
    }
    catch (const std::filesystem::filesystem_error& e) {
        view.displayMessage("Error getting file size: " + std::string(e.what()));
    }
}

void FileSizeCommand::setFileName(const std::string& name) {
    filename = name;
}
