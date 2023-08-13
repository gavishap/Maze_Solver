#ifndef MAZE_COMPRESSION_H
#define MAZE_COMPRESSION_H

#include <fstream>
#include <vector>
#include "Maze2d.h"
#include <cstdint>
class MazeCompression {
public:
    static void compressAndSave(const Maze2d& maze, const std::string& filename) {
        std::vector<char> data = maze.getData();
        std::vector<char> compressedData = compress(data);

        std::ofstream outFile(filename, std::ios::binary);
        for (char c : compressedData) {
            outFile.put(c);
        }
        outFile.close();
    }

    static Maze2d loadAndDecompress(const std::string& filename) {
        std::vector<char> compressedData;
        std::ifstream inFile(filename, std::ios::binary);
        char c;
        while (inFile.get(c)) {
            compressedData.push_back(c);
        }
        inFile.close();

        std::vector<char> decompressedData = decompress(compressedData);
        return Maze2d(decompressedData);
    }
    static void compressAndSaveSolution(const std::vector<std::pair<int, int>>& solution, const std::string& filename) {
        std::ofstream outFile(filename, std::ios::binary);
        std::cout << "Compressing and saving solution to file: " << filename << std::endl;

        for (const auto& coord : solution) {
            int16_t x = static_cast<int16_t>(coord.first);
            int16_t y = static_cast<int16_t>(coord.second);
            outFile.write(reinterpret_cast<char*>(&x), sizeof(int16_t));
            outFile.write(reinterpret_cast<char*>(&y), sizeof(int16_t));
        }
        outFile.close();
        std::cout << "Solution saved to file: " << filename << std::endl;

    }

    static std::vector<std::pair<int, int>> loadAndDecompressSolution(const std::string& filename) {
        std::vector<std::pair<int, int>> solution;
        std::ifstream inFile(filename, std::ios::binary);
        while (inFile.good()) {
            int16_t x, y;
            inFile.read(reinterpret_cast<char*>(&x), sizeof(int16_t));
            inFile.read(reinterpret_cast<char*>(&y), sizeof(int16_t));
            if (inFile.good()) {
                solution.emplace_back(x, y);
            }
        }
        inFile.close();
        return solution;
    }

private:
    static std::vector<char> compress(const std::vector<char>& data) {
        std::vector<char> compressed;
        int count = 1;
        for (size_t i = 1; i < data.size(); ++i) {
            if (data[i] == data[i - 1]) {
                count++;
            }
            else {
                compressed.push_back(data[i - 1]);
                compressed.push_back(count);
                count = 1;
            }
        }
        compressed.push_back(data.back());
        compressed.push_back(count);
        return compressed;
    }

    static std::vector<char> decompress(const std::vector<char>& compressedData) {
        std::vector<char> decompressed;
        for (size_t i = 0; i < compressedData.size(); i += 2) {
            char c = compressedData[i];
            int count = compressedData[i + 1];
            for (int j = 0; j < count; ++j) {
                decompressed.push_back(c);
            }
        }
        return decompressed;
    }
    
};

#endif // MAZE_COMPRESSION_H

