#ifndef MAZE_2D_H
#define MAZE_2D_H

#include <vector>
#include <utility>
#include <ostream>
#include <iostream>
#include "AbstractSearchable.h"


class Maze2d : public AbstractSearchable{
private:
    std::vector<std::vector<char>> mazeWithPlayer; // Using char to represent walls, paths, and the player
    Position start;
    Position end;
    Position playerPos;  // Current player position

public:

public:
    void markPosition(const Position& pos) {
        if (mazeWithPlayer[pos.y][pos.x] == ' ') {
            mazeWithPlayer[pos.y][pos.x] = 'X';
        }
        //else
        //{
        //    std::cout << "The posiiton is not empty, pos (" << pos.x << "," << pos.y << ") = '" << mazeWithPlayer[pos.y][pos.x] << "'" << std::endl;
        //}
    }

    void unmarkPosition(const Position& pos) {
        if (mazeWithPlayer[pos.y][pos.x] == 'X') {
            mazeWithPlayer[pos.y][pos.x] = ' ';
        }
    }
    //default constructor
    Maze2d()
        : mazeWithPlayer(2, std::vector<char>(2, '#')),
        start(0, 0),
        end(1, 1),
        playerPos(0, 0)
    {
        // Set the starting position to 'P' for player.
        mazeWithPlayer[start.y][start.x] = 'P';
        
    }

    Maze2d(int width, int height) : mazeWithPlayer(height, std::vector<char>(width, '#')), start(0, 0), end(width - 1, height - 1) {
        playerPos = start;
        updatePosition(playerPos, 'P');
    }
    int getWidth() const {
        if (mazeWithPlayer.empty()) {
            return 0;
        }
        return mazeWithPlayer[0].size();
    }

    int getHeight() const {
        return mazeWithPlayer.size();
    }

    Maze2d(const std::vector<char>& data) {
        int width = data[0];
        int height = data[1];

        mazeWithPlayer.resize(height, std::vector<char>(width));

        start = { data[2], data[3] };
        end = { data[4], data[5] };
        playerPos = start;

        int index = 6;
        for (int i = 0; i < height; ++i) {

            for (int j = 0; j < width; ++j) {
                mazeWithPlayer[i][j] = data[index++];
            }
        }
    }
    bool operator==(const Maze2d& other) const {
        if (start != other.start || end != other.end) {
            return false;
        }

        if (mazeWithPlayer.size() != other.mazeWithPlayer.size()) {
            return false;
        }

        for (size_t i = 0; i < mazeWithPlayer.size(); i++) {
            if (mazeWithPlayer[i] != other.mazeWithPlayer[i]) {
                return false;
            }
        }

        return true;
    }

    void setWall(int x, int y) {
        if (x == playerPos.x && y == playerPos.y)
        {
            return;
        }
        updatePosition({ x, y }, '#');
    }

    void setFree(int x, int y) {
        if (x == playerPos.x && y == playerPos.y)
        {
            return;
        }
        updatePosition({ x, y }, ' ');
    }

    void set_start(int x, int y) {
        updatePosition(playerPos, '#');
        start = { x, y };
        playerPos = start; 
        updatePosition(playerPos, 'P');  
        setFree(x, y);
    }


    void set_end(int x, int y) {
        end = { x, y };
        setFree(x, y);
    }

    std::vector<Position> get_neighbors(const Position& p) const override {
        size_t x = p.x;
        size_t y = p.y;
        std::vector<Position> neighbors;
        if (x > 0) neighbors.push_back(Position(x - 1, y));
        if (x < mazeWithPlayer[0].size() - 1) neighbors.push_back(Position(x + 1, y));
        if (y > 0) neighbors.push_back(Position(x, y - 1));
        if (y < mazeWithPlayer.size() - 1) neighbors.push_back(Position(x, y + 1));
        return neighbors;
    }

    bool is_wall(int x, int y) const {
        return mazeWithPlayer[y][x] == '#';
    }

    bool is_free(int x, int y) const {
        return mazeWithPlayer[y][x] == ' ';
    }

    Position getStartPosition() const override {
        return start;
    }

    Position getGoalPosition() const override {
        return end;
    }

    
    Position getPlayerPosition() const {
        return playerPos;
    }

    bool isGoal(const Position& p) const override {

        return (p.x == getGoalPosition().x && p.y== getGoalPosition().y);
    }

    bool movePlayer(char direction) {
        Position newPos = playerPos;
        switch (direction) {
        case 'W': newPos.y--; break;
        case 'A': newPos.x--; break;
        case 'S': newPos.y++; break;
        case 'D': newPos.x++; break;
        }

        if (is_free(newPos.x, newPos.y)) {
            updatePosition(playerPos, ' ');  
            playerPos = newPos;
            updatePosition(playerPos, 'P'); 
            return true;
        }

        return false;
    }

    std::vector<std::string> getPossibleMoves(Position p) const {
        std::vector<std::string> moves;
        std::vector<Position> neighbors = get_neighbors(p);
        for (auto& neighbor : neighbors) {
            if (is_free(neighbor.x, neighbor.y)) {
                if (neighbor.x > p.x) moves.push_back("Right");
                else if (neighbor.x < p.x) moves.push_back("Left");
                else if (neighbor.y > p.y) moves.push_back("Down");
                else if (neighbor.y < p.y) moves.push_back("Up");
            }
        }
        return moves;
    }

    friend std::ostream& operator<<(std::ostream& os, const Maze2d& m) {
        for (const auto& row : m.mazeWithPlayer) {
            for (char cell : row) {
                os << cell;
            }
            os << std::endl;
        }
        return os;
    }

    std::vector<char> getData() const {
        std::vector<char> data;

        // Add width and height
        int width = mazeWithPlayer[0].size();
        int height = mazeWithPlayer.size();
        data.push_back(width);
        data.push_back(height);

        // Add start position
        data.push_back(start.x);
        data.push_back(start.y);

        // Add end position
        data.push_back(end.x);
        data.push_back(end.y);

        // Add maze contents
        for (const auto& row : mazeWithPlayer) {
            for (char cell : row) {
                data.push_back(cell);
            }
        }

        return data;
    }


private:
    void updatePosition(const Position& pos, char symbol) {
        mazeWithPlayer[pos.y][pos.x] = symbol;
    }
};

#endif // MAZE_2D_H
