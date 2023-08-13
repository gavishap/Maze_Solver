#ifndef ASTAR_H
#define ASTAR_H
#include "../../Model/AbstractSearcher.h"
#include "../../Model/AbstractMaze2dGenerator.h"
#include <queue>
#include <unordered_set>
#include <map>
#include <iostream>
#include "../../Model/Maze2d.h"


class AStar : public AbstractSearcher {
public:
    struct Cell {
        Position position;
        Position parentCellPosition;
        float f, g, h;
    };
    
    struct CellCompare {
        bool operator()(const Cell& a, const Cell& b) const {
            return a.f > b.f;
        }
    };
    
    AStar(Maze2d* maze) : maze(maze) {
        if (maze->is_wall(maze->getStartPosition().x, maze->getStartPosition().y)) {
            std::cout << "No start cell found" << std::endl;
        }
    }

    std::vector<Position> search(const AbstractSearchable& searchable) override {
        std::priority_queue<Cell, std::vector<Cell>, CellCompare> priorityQueue;

        startCell = maze->getStartPosition();
        goalCell = maze->getGoalPosition();

        priorityQueue.push({ startCell, startCell, 0, 0, heuristic(startCell) });

        while (!priorityQueue.empty()) {
            Cell current = priorityQueue.top();
            priorityQueue.pop();

            if (current.position == goalCell) {
                searched.push_back(current);
                return retracePath(current);
            }

            addNeighboursToQueue(current, priorityQueue);
            searched.push_back(current);

        }

        return std::vector<Position>();
    }


private:
    Maze2d* maze;
    Position startCell, goalCell;

    float heuristic(const Position& pos) {
        // Manhattan distance
        return static_cast<float>(std::abs(pos.x - goalCell.x) + std::abs(pos.y - goalCell.y));

    }

    std::vector<Position> retracePath(Cell cell) {
        std::vector<Position> path;
        Position current = cell.position;
        while (current != startCell) {
            path.push_back(current);
            current = getCellFromPosition(current).parentCellPosition;
        }
        path.push_back(startCell);

        return path;
    }

    Cell getCellFromPosition(const Position& pos) {
        for (const auto& cell : searched) {
            if (cell.position == pos) {
                return cell;
            }
        }
        return { {0, 0}, {0, 0}, 0, 0, 0 };  // Return a dummy value
    }
    void addNeighboursToQueue(const Cell& cell, std::priority_queue<Cell, std::vector<Cell>, CellCompare>& priorityQueue) {
        for (const auto& neighbor : maze->get_neighbors(cell.position)) {
            if (maze->is_free(neighbor.x, neighbor.y) && !isVisited(neighbor)) {
                float g = cell.g + 1;  
                float h = heuristic(neighbor);
                priorityQueue.push({ neighbor, cell.position, g + h, g, h });
            }
        }
    }

    bool isVisited(const Position& pos) {
        for (const auto& cell : searched) {
            if (cell.position == pos) {
                return true;
            }
        }
        return false;
    }

    std::vector<Cell> searched;
};

#endif // ASTAR_H
