#ifndef LOD_H
#define LOD_H

#include "Path.h"

class Lod : public Path {
public:
    Lod(TerrainMap& map, Point start, Point finish)
        : Path(map, "Lod", start, finish) {}
    bool find() override; // Implements Dijkstra's algorithm with elevation constraint
};

#endif