#include "Map.h"
#include "DinoNames.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

Map::Map(const int scale, const int countCarnivore, const int countHerbivore)
: map(scale), scale(scale)
{
    for(auto& inner : map)
    {
        inner.resize(scale);
    }

    int countFence = (int) (scale * scale * 0.1);
    addTypeBulk(FENCE, countFence);
    addTypeBulk(CARNIVORE, countCarnivore);
    addTypeBulk(HERBIVORE, countHerbivore);
}

Map::datatype Map::getCoordninates(const int x, const int y) const {
    return map[x][y];
}

Map::datatype Map::getCoordninates(const Coordinate & coord) const {
    return getCoordninates(coord.x, coord.y);
}

void Map::setCoordninates(Coordinate const & coord, Map::datatype const & obj)
{
    map.at(coord.x).at(coord.y) = std::move(obj);
}

void Map::addTypeBulk(const MapObjectType &type, const int count) {
    for(int i = 0 ; i<count; i++){
        int x,y;
        do { // loop until an empty place is found
            x = Map::random0To20();
            y = Map::random0To20();
        } while(getCoordninates(x,y) != nullptr);

        setCoordninates(Coordinate(x,y), Map::makeTypeInstance(type, i));
    }
}

unique_ptr<MapObject> Map::makeTypeInstance(const MapObjectType &type, const int id) {
    switch (type) {
        case CARNIVORE:
            return make_unique<Carnivore>(id, namesCarnivore[id]);
        case HERBIVORE:
            return make_unique<Herbivore>(id, namesHerbivore[id]);
        case FENCE:
            return make_unique<Fence>();
        default: throw std::invalid_argument("cant add type");
    }
}

int Map::random0To20(){
    return rand() % 20;
}

std::ostream &operator<<(std::ostream &strm, const Map &a) {
    // separator line
    auto makeSeperator = [&] {
        for (int i = 0; i < a.scale; i++)
            strm << "-----";
        strm << "--\n";
    };

    makeSeperator();

    // loop through the rows
    for(auto const & row: a.map){
        strm << "|";
        for(auto const &  cell: row){
            if(cell == nullptr)
                strm << "     ";
            else
                strm << *cell;
        }
        strm << "|\n";
    }

    makeSeperator();

    return strm;
}

MapObjectType Map::checkCoordinates(const int x, const int y) const {
    if(map[x][y] == nullptr) return EMPTY;
    return map[x][y]->getType();
}

MapObjectType Map::checkCoordinates(const Coordinate &coord) const {
    return checkCoordinates(coord.x, coord.y);
}


unsigned int Map::countType(const MapObjectType & type) const {
    int count = 0;

    for(auto const & row: map){
        for(auto const & cell: row){
            if(cell == nullptr) continue;
            if(cell->getType() == type)
                count++;
        }
    }
    return count;
}

void Map::eatAll() {
    walk([&](Coordinate coord){eat(coord);});
}

void Map::eat(Coordinate const & coord) {

    if(getCoordninates(coord) == nullptr) return;
    if(getCoordninates(coord)->getType() != CARNIVORE) return;
    if(!Carnivore::attemptEat()) return;

    auto const neighbors = getNeighbors(coord);
    vector<Coordinate> herbivoreNeighbors;

    std::copy_if(begin(neighbors), end(neighbors), back_inserter(herbivoreNeighbors), [&](Coordinate const & coord){
        if(getCoordninates(coord) == nullptr) return false;
        if(getCoordninates(coord)->getType() != HERBIVORE) return false;
        return true;
    });

    if(herbivoreNeighbors.empty()) return;

    auto targetCoord = herbivoreNeighbors.at(rand() % herbivoreNeighbors.size());
    setCoordninates(targetCoord, nullptr);
}

void Map::moveAll() {
    walk([&](Coordinate coord){move(coord);});

    moveReset();
}

void Map::move(Coordinate const & coord) {
    if(!getCoordninates(coord)->canMove())
        return;

    auto const neighbors = getNeighbors(coord);

    vector<Coordinate> emptyNeighbors;

    std::copy_if(begin(neighbors), end(neighbors), back_inserter(emptyNeighbors), [&](Coordinate const & coord){
        return getCoordninates(coord) == nullptr;
    });

    auto targetCoord = emptyNeighbors.at(rand() % emptyNeighbors.size());
    setCoordninates(targetCoord, getCoordninates(coord));
    setCoordninates(coord, nullptr);
}

void Map::moveReset() {
    for(auto const & row: map){
        for(auto const & cell: row){
            if(cell == nullptr) continue;
            cell->hasMovedReset();
        }
    }
}

bool Map::isValidCoord(Coordinate &cord) const {
    return !(cord.x < 0 || cord.x >= scale || cord.y < 0 || cord.y >= scale);
}

vector<Coordinate> Map::getNeighbors(Coordinate const &center) const {
    vector<Coordinate> out;

    for(int dx=-1; dx < 2; dx++){
        for(int dy=-1; dy < 2; dy++){
            if(dx == 0 && dy == 0) continue;
            Coordinate neighbor;
            neighbor.x = center.x + dx;
            neighbor.y = center.y + dy;

            if(!isValidCoord(neighbor))
                continue;
            out.push_back(neighbor);
        }
    }
    return out;
}





