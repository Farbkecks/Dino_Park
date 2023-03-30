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
    Map(int scale, int countCarnivore,int countHerbivore);

    unsigned int countType(const MapObjectType & type) const;

    void eatAll();

    void moveAll();

private:
    //variables
    const int scale;

    std::vector<std::vector<datatype>> map;

    friend std::ostream &operator<<(std::ostream &strm, const Map &a);

private:
    //funktions
    void setCoordninates(Coordinate const & coord, datatype const & obj);

    datatype getCoordninates(const Coordinate & coord) const;
    datatype getCoordninates(int x, int y) const;

    MapObjectType checkCoordinates(int x,int y) const;
    MapObjectType checkCoordinates(const Coordinate & coord) const;

    bool isValidCoord(Coordinate & cord) const;

    std::vector<Coordinate> getNeighbors(Coordinate const & center) const;

    template<class T>
    void walk(T walkFunc);

    void addTypeBulk(const MapObjectType &type, const int count);

    static std::unique_ptr<MapObject> makeTypeInstance(const MapObjectType &type, const int id);

    static int random0To20();

    void eat(Coordinate const & coord);
    void move(Coordinate const & coord);

    void moveReset();

};

// streams out the map
std::ostream &operator<<(std::ostream &strm, const Map &a);

template<class T>
void Map::walk(T walkFunc) {
    for (int x = 0; x < scale; x++) {
        for (int y = 0; y < scale; y++) {
            if (getCoordninates(x,y) == nullptr) continue;
            walkFunc(Coordinate(x,y));
        }
    }
}