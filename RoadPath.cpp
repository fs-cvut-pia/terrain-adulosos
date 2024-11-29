#include "RoadPath.h"
#include <set>

bool RoadPath::find() {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::map<Point, Point> cameFrom;
    std::map<Point, double> costSoFar;

    openSet.push({start, 0, heuristic(start, finish)});
    costSoFar[start] = 0;

    const std::vector<Point> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.point == finish) {
            // Rekonstrukce cesty
            Point p = finish;
            path.push_back(p);
            while (p != start) {
                p = cameFrom[p];
                path.push_back(p);
            }
            std::reverse(path.begin(), path.end());
            return true;
        }

        for (const Point& dir : directions) {
            Point neighbor = current.point + dir;
            if (!map.validCoords(neighbor)) continue;

            // Validace nadmořské výšky a stoupání
            if (!isValidStep(current.point, neighbor)) continue;

            double newCost = costSoFar[current.point] + 1; // Vzdálenost mezi sousedy je 1
            if (costSoFar.find(neighbor) == costSoFar.end() || newCost < costSoFar[neighbor]) {
                costSoFar[neighbor] = newCost;
                double priority = newCost + heuristic(neighbor, finish);
                openSet.push({neighbor, newCost, heuristic(neighbor, finish)});
                cameFrom[neighbor] = current.point;
            }
        }
    }

    return false; // Cesta nenalezena
}

bool RoadPath::isValidStep(Point current, Point next) const {
    int currentHeight = map.alt(current);
    int nextHeight = map.alt(next);

    // Kontrola nadmořské výšky
    if (nextHeight <= 0) return false;

    // Výpočet stoupání
    double elevationChange = nextHeight - currentHeight;
    double horizontalDistance = std::sqrt((next.x - current.x) * (next.x - current.x) +
                                          (next.y - current.y) * (next.y - current.y));

    double slope = elevationChange / horizontalDistance;

    return slope < 0.06; // Stoupání < 6 %
}
