#ifndef SHIPPATH_H
#define SHIPPATH_H

#include "Path.h"
#include <queue>
#include <cmath>
#include <map>

// Class for "Loď" path finding
class ShipPath : public Path {
public:
    ShipPath(TerrainMap& m, std::string name_in, Point start_in, Point finish_in)
        : Path(m, name_in, start_in, finish_in) {}

    bool find() override;

private:
    struct Node {
        Point point;
        double cost;
        double heuristic;
        bool operator>(const Node& other) const {
            return (cost + heuristic) > (other.cost + other.heuristic);
        }
    };

    double heuristic(Point a, Point b) const {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

#endif // SHIPPATH_H
