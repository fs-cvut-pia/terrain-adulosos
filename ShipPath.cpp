#include "ShipPath.h"
#include <iostream>

ShipPath::ShipPath(TerrainMap& terrain, const std::string& name, const Point& start, const Point& finish)
    : Path(terrain, name, start, finish) {}

bool ShipPath::find() {
    using QueueElement = std::pair<double, Point>;
    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<>> queue;

    std::map<Point, double> distance;
    std::map<Point, Point> predecessor;

    // Inicializace startovního bodu
    distance[start] = 0.0;
    queue.push({0.0, start});

    // Prohledávání mapy
    while (!queue.empty()) {
        auto [current_dist, current] = queue.top();
        queue.pop();

        if (current == finish) break; // Pokud jsme na cíli, ukončíme hledání

        if (current_dist > distance[current]) continue; // Přeskočíme, pokud je vzdálenost neaktuální

        for (const Point& dir : directions) {
            Point neighbor = current + dir;

            // Kontrola platnosti souseda
            if (!terrain.validCoords(neighbor)) continue;

            int height = terrain.alt(neighbor);
            if (height >= 0 && neighbor != start && neighbor != finish) continue; // Nepřístupný bod

            double step_cost = dir.length();
            double new_dist = current_dist + step_cost;

            if (new_dist < distance[neighbor] || distance.find(neighbor) == distance.end()) {
                distance[neighbor] = new_dist;
                predecessor[neighbor] = current;
                queue.push({new_dist, neighbor});
            }
        }
    }

    if (predecessor.find(finish) == predecessor.end()) {
        return false; // Cesta nebyla nalezena
    }

    Point current = finish;
    while (current != start) {
        path.push_back(current);
        current = predecessor[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return true; // Cesta byla nalezena
}
