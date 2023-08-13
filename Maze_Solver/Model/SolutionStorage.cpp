#include "SolutionStorage.h"
#include <filesystem> 
#include <fstream>    
#include "MazeCompression.h"
#include <iostream>
namespace fs = std::filesystem;

void SolutionStorage::addSolution(const std::string& mazeName, const std::vector<std::pair<int, int>>& solutionPath) {
    solutions[mazeName] = solutionPath;
    std::cout << "Added solution for maze named: " << mazeName << " with size: " << solutionPath.size() << std::endl;

}

std::vector<std::pair<int, int>> SolutionStorage::getSolution(const std::string& mazeName) {
    if (solutionExists(mazeName)) {
        std::cout << "Solution exists" << std::endl;
        return solutions[mazeName];
    }
    std::cout << "Solution doesnt exists" << std::endl;
    return std::vector<std::pair<int, int>>();
}

bool SolutionStorage::solutionExists(const std::string& mazeName) {
    return solutions.find(mazeName) != solutions.end();
}
bool SolutionStorage::isEmpty() const {
    return solutions.empty();
}

void SolutionStorage::saveSolutionToFile(const std::string& mazeName) {
    if (solutionExists(mazeName)) {
        std::string filename = generateFilename(mazeName);
        std::cout << "Saving solution for maze named: " << mazeName << " to file: " << filename << std::endl;
        MazeCompression::compressAndSaveSolution(solutions[mazeName], filename);
        std::cout << "Solution for maze named: " << mazeName << " saved successfully." << std::endl;

    }
}

void SolutionStorage::loadSolutionFromFile(const std::string& mazeName) {
    std::string filename = generateFilename(mazeName);
    solutions[mazeName] = MazeCompression::loadAndDecompressSolution(filename);
}

void SolutionStorage::loadAllSolutions() {
    for (const auto& entry : fs::directory_iterator(".")) { 
        if (entry.path().extension() == ".mz") {
            std::string mazeName = entry.path().stem().string(); // Remove ".mz" extension
            loadSolutionFromFile(mazeName);
        }
    }
}

void SolutionStorage::saveAllSolutions() {
    for (const auto& [mazeName, solutionPath] : solutions) {
        saveSolutionToFile(mazeName);
    }
}
