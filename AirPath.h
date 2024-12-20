#ifndef AIRPATH_H
#define AIRPATH_H

#include "Path.h"
#include <queue>
#include <cmath>
#include <map>

// Class for "Letadlo" path finding
class AirPath : public Path {
public:
    AirPath(TerrainMap& m, std::string name_in, Point start_in, Point finish_in)
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

#endif
