#ifndef SOLUTIONSTORAGE_H
#define SOLUTIONSTORAGE_H

#include "MazeCompression.h"
#include <unordered_map>
class SolutionStorage {
private:
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> solutions; // Stores solutions by maze name

    // Generate a filename for a maze's solution
    std::string generateFilename(const std::string& mazeName) {
        return mazeName + ".mz";
    }

public:
    // Adds a solution to storage
    void addSolution(const std::string& mazeName, const std::vector<std::pair<int, int>>& solutionPath);

    // Retrieves a solution by maze name
    std::vector<std::pair<int, int>> getSolution(const std::string& mazeName);

    // Checks if a solution for the given maze name exists in storage
    bool solutionExists(const std::string& mazeName);

    // Saves a solution to a file
    void saveSolutionToFile(const std::string& mazeName);

    // Loads a solution from a file
    void loadSolutionFromFile(const std::string& mazeName);

    // Call this at program startup to load all solutions from files
    void loadAllSolutions();

    // Call this at program exit to save all solutions to files
    void saveAllSolutions();
    bool isEmpty() const;
        

};
#endif