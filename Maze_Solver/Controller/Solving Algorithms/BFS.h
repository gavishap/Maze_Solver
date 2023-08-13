#ifndef BFS_H
#define BFS_H

#include "../../Model/AbstractSearcher.h"
#include <deque>
#include <unordered_set>
#include <map>
#include <iostream>
#include "../../Model/Maze2d.h"  

struct PositionHasher {
    std::size_t operator()(const Position& p) const {
        return p.x ^ (p.y << 1);
    }
};

struct PositionComparator {
    bool operator()(const Position& a, const Position& b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

class BFS : public AbstractSearcher {
public:
    struct Cell {
        Position position;
        Position parentCellPosition;
    };

    BFS(Maze2d* maze) : maze(maze) {
        if (maze->is_wall(maze->getStartPosition().x, maze->getStartPosition().y)) {
            std::cout << "No start cell found" << std::endl;
        }
    }

    std::vector<Position> search(const AbstractSearchable& searchable) override {
        // Initialization
        startCell = maze->getStartPosition();
        deque.push_back({ startCell, startCell });
        
        while (!deque.empty()) {
            Cell current = deque.front();
            deque.pop_front();

            if (endFound(current)) {
                searched.push_back(current);
                return retracePath(current);
            }

            addNeighboursToQueue(current);
            searched.push_back(current);
        }

        return std::vector<Position>();
    }

    void PrintSearched()
    {
        std::cout << "Print list of searches cells:" << std::endl;

        for (const auto& cell : searched)
        {
            std::cout << "cell = (" << cell.position.x << "," << cell.position.y << ")" << std::endl;
        }
    }

private:
    Maze2d* maze;
    std::deque<Cell> deque;
    std::vector<Cell> searched;
    Position startCell;

    std::vector<Position> retracePath(Cell cell) {
        std::vector<Position> path;
        Position current = cell.position;
        while (current != startCell) {
            path.push_back(current);
            maze->markPosition(current);
            current = getCellFromPosition(current).parentCellPosition;
        }
        path.push_back(startCell);
        maze->markPosition(startCell);

        return path;
    }

    Cell getCellFromPosition(const Position& pos) {
       // std::cout << "pos = (" << pos.x << "," << pos.y << ")" << std::endl;
       //PrintSearched();
        for (const auto& cell : searched) {
            if (cell.position.x == pos.x && cell.position.y == pos.y) {
                return cell;
            }
        }
        return { {0, 0}, {0, 0} };  // Return a dummy value
    }

    bool endFound(const Cell& cell) {
        for (const auto& neighbor : maze->get_neighbors(cell.position)) {
            if (maze->isGoal(neighbor)) {
                return true;
            }
        }
        return false;
    }

    void addNeighboursToQueue(const Cell& cell) {
        for (const auto& neighbor : maze->get_neighbors(cell.position)) {
            if (maze->is_free(neighbor.x, neighbor.y) && !isVisited(neighbor)) {
                deque.push_back({ neighbor, cell.position });
            }
        }
    }

    bool isVisited(const Position& pos) {
        for (const auto& cell : searched) {
            if (cell.position.x == pos.x && cell.position.y == pos.y) {
                return true;
            }
        }
        return false;
    }
};

#endif // BFS_H
