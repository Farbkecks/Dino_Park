#pragma once
#include "Carnivore.h"
#include "Herbivore.h"
#include "MapObject.h"
#include <vector>
#include <memory>

class Map {
public:
    Map(int scale);

    void setObject(const int x, const int y, std::shared_ptr<MapObject> obj);
    std::shared_ptr<MapObject> get(const int x, const int y) const;
private:
    typedef std::shared_ptr<MapObject> datatype;
    std::vector<std::vector<datatype>> map;
};
