#pragma once
#include "Carnivore.h"
#include "Herbivore.h"
#include "MapObject.h"
#include <vector>
#include <memory>

class Map {
public:
    Map(const int scale, const int countCarnivore, const int countHerbivore);
    void setObject(const int x, const int y, std::shared_ptr<MapObject> obj);
    std::shared_ptr<MapObject> getCoordninates(const int x, const int y) const;
private:
    typedef std::shared_ptr<MapObject> datatype;
    std::vector<std::vector<datatype>> map;
    void addTypeBulk(const MapObjectType & type, const int count);
    void addType(const int x, const int y, const MapObjectType & type, const int id);
    int randrom0To20() const;
    friend std::ostream &operator<<(std::ostream &strm, const Map &a);
    std::string toText() const;
    const int scale;
};
std::ostream &operator<<(std::ostream &strm, const Map &a);