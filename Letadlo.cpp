#include "Letadlo.h"
#include <queue>
#include <limits>
#include <map>
#include <algorithm>

bool Letadlo::find() {
    // Priority queue for Dijkstra's algorithm
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> pq;
    std::map<Point, double> distances;
    std::map<Point, Point> previous;

    // Initialize distances to infinity
    for (int x = 0; x < map.nx; ++x) {
        for (int y = 0; y < map.ny; ++y) {
            distances[{x, y}] = std::numeric_limits<double>::infinity();
        }
    }

    // Set start point distance to 0 and push to the queue
    distances[start] = 0.0;
    pq.push({0.0, start});

    const std::vector<Point> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    while (!pq.empty()) {
        auto [current_dist, current] = pq.top();
        pq.pop();

        // If we reached the finish, break
        if (current == finish) break;

        for (const auto& dir : directions) {
            Point neighbor = current + dir;
            if (!map.validCoords(neighbor)) continue;

            double new_dist = current_dist + dir.length();

            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                previous[neighbor] = current;
                pq.push({new_dist, neighbor});
            }
        }
    }

    // Reconstruct path
    if (distances[finish] == std::numeric_limits<double>::infinity()) return false;

    Point step = finish;
    while (step != start) {
        path.push_back(step);
        step = previous[step];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return true;
}