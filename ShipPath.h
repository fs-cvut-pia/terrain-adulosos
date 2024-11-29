#ifndef SHIPPATH_H
#define SHIPPATH_H

#include "Path.h"
#include "TerrainMap.h"
#include "Point.h"
#include <vector>
#include <string>
#include <map>
#include <queue>

class ShipPath : public Path {
public:
    ShipPath(TerrainMap& terrain, const std::string& name, const Point& start, const Point& finish);

    bool find() override; // Návratový typ upraven na bool

private:
    std::vector<Point> directions =
