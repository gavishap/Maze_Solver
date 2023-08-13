#ifndef ABSTRACT_SEARCHABLE_H
#define ABSTRACT_SEARCHABLE_H

#include <vector>
#include <ostream>

class Position {
public:
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator!=(const Position& other) const {
        return x != other.x || y != other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
        os << "(" << pos.x << ", " << pos.y << ")";
        return os;
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

};

class AbstractSearchable {
public:
    virtual ~AbstractSearchable() {}

    virtual Position getStartPosition() const = 0;
    virtual Position getGoalPosition() const = 0;
    virtual std::vector<Position> get_neighbors(const Position& p) const = 0;
    virtual bool isGoal(const Position& p) const = 0;
};

#endif // ABSTRACT_SEARCHABLE_H
