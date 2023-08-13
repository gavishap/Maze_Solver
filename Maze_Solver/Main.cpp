#include <iostream>
#include <vector>
#include <conio.h>  
#include "../Maze_Solver/Model/AbstractMaze2dGenerator.h"
#include "../Maze_Solver/Model/MyMaze2dGenerator.h"
#include "../Maze_Solver/Controller/Solving Algorithms/BFS.h"  
#include "../Maze_Solver/Model/MazeCompression.h"
#include "../Maze_Solver/Controller/Solving Algorithms/AStar.h"
#include "../Maze_Solver/View/CLI.h"
#include "../Maze_Solver/Controller/Controller.h"
class TestMazeGenerator {
public:
    TestMazeGenerator() {}

    void testMazeGenerator(Maze2dGenerator& mg) {
        std::cout << mg.measureAlgorithmTime(16, 16) << std::endl;
        Maze2d maze = mg.generate(20, 20);
        Position p = maze.getStartPosition();
        std::cout << p << std::endl;

        // Save maze to file
        std::string filename = "maze.bin";
        MazeCompression::compressAndSave(maze, filename);

        // Get size of saved file
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        file.close();
        std::cout << "Size of the saved maze file: " << size << " bytes" << std::endl;

        // Load maze from file and compare
        Maze2d loadedMaze = MazeCompression::loadAndDecompress(filename);
        if (maze == loadedMaze) {
            std::cout << "The loaded maze is identical to the original maze." << std::endl;
        }
        else {
            std::cout << "The loaded maze is not the same as the original maze." << std::endl;
        }
        std::cout << "Would you like to solve the maze manually (M) or use BFS (B)? or A for A* ";
        char choice = _getch(); // Wait for user input
        if (choice == 'A' || choice == 'a') {
            // Use A* to find the solution path.
            AStar aStar(&maze);
            std::cout << "Built AStar searcher object" << std::endl;
            std::vector<Position> solutionPath = aStar.search(maze);

            // Displaying the number of steps in the solution.
            std::cout << "Solution path found using A* has " << solutionPath.size() << " steps." << std::endl;

            // Traverse the maze based on the solution path.
            for (const Position& position : solutionPath) {
                maze.markPosition(position);
            }

            // Printing the maze with the solution path.
            std::cout << "Here is the solution path using A*:" << std::endl;
            std::cout << maze << std::endl;

            std::cout << "Congratulations! You reached the end of the maze using A*!" << std::endl;
        }

        if (choice == 'B' || choice == 'b') {
            // Use BFS to find the solution path.
            BFS bfs(&maze);
            std::cout << "Built BFS searcher object" << std::endl;
            std::vector<Position> solutionPath = bfs.search(maze);
            
           // bfs.PrintSearched();

            //std::cout << "Traversing the maze based on the solution path, size = " << solutionPath.size() << std::endl;
            // Traverse the maze based on the solution path.
            for (const Position& position : solutionPath) {
                maze.markPosition(position);
            }

            std::cout << "Here is the solution path using BFS:" << std::endl;
            std::cout << maze << std::endl;

            std::cout << "Congratulations! You reached the end of the maze using BFS!" << std::endl;

        }
        else if (choice == 'M' || choice == 'm') {
            // Manual maze traversal logic.
            while (p != maze.getGoalPosition()) {
                system("cls");
                std::cout << maze << std::endl;

                std::cout << std::endl << "Goal position: (" << maze.getGoalPosition().x << "," << maze.getGoalPosition().y << ")" << std::endl;

                std::vector<std::string> moves = maze.getPossibleMoves(p);
                std::cout << "Possible moves: ";
                for (const std::string& move : moves) {
                    std::cout << move << " ";
                }
                std::cout << std::endl << "Use W (up), A (left), S (down), D (right) to move: ";

                char input = _getch();  // Wait for a key press
                switch (input) {
                case 'W':
                case 'w':
                    if (std::find(moves.begin(), moves.end(), "Up") != moves.end()) {
                        maze.movePlayer('W');
                    }
                    break;
                case 'A':
                case 'a':
                    if (std::find(moves.begin(), moves.end(), "Left") != moves.end()) {
                        maze.movePlayer('A');
                    }
                    break;
                case 'S':
                case 's':
                    if (std::find(moves.begin(), moves.end(), "Down") != moves.end()) {
                        maze.movePlayer('S');
                    }
                    break;
                case 'D':
                case 'd':
                    if (std::find(moves.begin(), moves.end(), "Right") != moves.end()) {
                        maze.movePlayer('D');
                    }
                    break;
                }
                p = maze.getPlayerPosition();  // Update player's position
            }

            std::cout << "Congratulations! You reached the end of the maze!" << std::endl;
        }
        else {
            std::cout << "Invalid choice. Exiting." << std::endl;
            return;
        }
    }
};



int main() {
    //If you want to play the game manually then uncomment this next part
   /* MyMaze2dGenerator generator;
    TestMazeGenerator test;
    test.testMazeGenerator(generator);*/

   Controller controller;
    CLI cli(std::cin, std::cout, controller);
    cli.start();

    return 0;

}
