#pragma once

#include "Carnivore.h"
#include "Herbivore.h"
#include "Fence.h"
#include "MapObject.h"
#include <vector>
#include <memory>

struct Coordinate
{
    Coordinate() = delete;
    Coordinate(int x, int y)
    : x(x), y(y) {}
    int x{}, y{};
};

class Map {
private:
    //variables
    typedef std::shared_ptr<MapObject> datatype;

    const int scale;

    std::vector<std::vector<datatype>> map;

    friend std::ostream &operator<<(std::ostream &strm, const Map &a);

public:
    //funktions
    Map(int scale, int countCarnivore,int countHerbivore);

    unsigned int countType(const MapObjectType & type) const;

    void eatAll();

    void moveAll();

    void setCoordninates(Coordinate const & coord, datatype const & obj);

    datatype getCoordninates(const Coordinate & coord) const;
    datatype getCoordninates(int x, int y) const;
    datatype & getReference(Coordinate coord);

    MapObjectType checkCoordinates(int x,int y) const;
    MapObjectType checkCoordinates(const Coordinate & coord) const;

public:
    //Iterator
    struct Iterator{
    public:
        Iterator(Coordinate coord, Map & map) : coord(coord), map(map) {}

        Coordinate getCoordinate() const {return coord; }

        datatype & operator*() const { return map.getReference(coord); }

        // Prefix increment
        Iterator& operator++();
        // Suffix operator
        Iterator operator++(int);

        bool operator== (const Iterator& other) { return (coord.x == other.coord.x && coord.y == other.coord.y); };
        bool operator!= (const Iterator& other) { return (coord.x != other.coord.x && coord.y != other.coord.y); };

    private:
        Coordinate coord;
        Map & map;
    };
    auto begin() { return Iterator(Coordinate(0,0), *this); }
    auto end()   { return Iterator(Coordinate(scale,scale), *this); }

    static std::vector<Coordinate> get_neighbours(Iterator const & it);

private:

    //functions
    bool isValidCoord(Coordinate & cord) const;

    std::vector<Coordinate> getNeighbors(Coordinate const & center) const;

    template<class T>
    void addTypeBulk(int count);

    static int random0To20();

    void moveReset();

};

// streams out the map
std::ostream &operator<<(std::ostream &strm, const Map &a);

template<class T>
void Map::addTypeBulk(const int count) {
    for(int i = 0 ; i<count; i++){
        int x,y;
        do { // loop until an empty place is found
            x = Map::random0To20();
            y = Map::random0To20();
        } while(getCoordninates(x,y) != nullptr);

        setCoordninates(Coordinate(x,y), std::make_shared<T>());
    }
}