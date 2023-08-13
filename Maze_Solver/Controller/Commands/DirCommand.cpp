#include "DirCommand.h"
#include <filesystem>
#include <sstream>

void DirCommand::execute() {
    if (dirPath.empty()) {
        dirPath = std::filesystem::current_path().string();  // Default to the current directory
    }

    std::stringstream ss;
    ss << "Contents of directory: " << dirPath << "\n";

    try {
        for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
            ss << entry.path().filename().string() << "\n";
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        ss << "Error reading directory: " << e.what() << "\n";
    }

    view.displayMessage(ss.str());
}
