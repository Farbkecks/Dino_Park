#pragma once

#include "Carnivore.h"
#include "Herbivore.h"
#include "Fence.h"
#include "MapObject.h"
#include <vector>
#include <memory>

struct Coordinate
{
    Coordinate() = default;
    Coordinate(int x, int y)
    : x(x), y(y) {}
    int x{}, y{0};
};

class Map {
private:
    typedef std::shared_ptr<MapObject> datatype;

public:
    Map(const int scale, const int countCarnivore, const int countHerbivore);

    void setObject(const int x, const int y, datatype const obj);

    datatype getCoordninates(const Coordinate coord) const;
    datatype getCoordninates(const int x, const int y) const;

    void setCoordninates(const Coordinate coord, datatype const obj);

    MapObjectType checkCoordinates(const int x, const int y) const;

    unsigned int countType(const MapObjectType type) const;

    void eatAll();
    void moveAll();

    template<class T>
    void walk(T walkFunc);

    bool isValidCoord(Coordinate & cord) const;
    std::vector<Coordinate> getNeighbors(Coordinate const & center) const;


private:

    const int scale;

    friend std::ostream &operator<<(std::ostream &strm, const Map &a);

    std::vector<std::vector<datatype>> map;

    void addTypeBulk(const MapObjectType &type, const int count);

    static std::unique_ptr<MapObject> makeTypeInstance(const MapObjectType &type, const int id);

    static int random0To20();

    void eat(const int x, const int y);
    void move(const int x, const int y);

    void moveReset();

};

// streams out the map
std::ostream &operator<<(std::ostream &strm, const Map &a);

template<class T>
void Map::walk(T walkFunc) {
    for (int x = 0; x < scale; x++) {
        for (int y = 0; y < scale; y++) {
            if (map[x][y] == nullptr) continue;
            walkFunc(x, y);
        }
    }
}