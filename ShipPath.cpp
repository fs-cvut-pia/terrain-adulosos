#include "ShipPath.h"
#include <set>

bool ShipPath::find() {
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
            // Kontrola výšky
            int height = map.alt(neighbor);
            if (height >= 0 && neighbor != start && neighbor != finish) continue;

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
