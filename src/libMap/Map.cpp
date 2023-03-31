#include "Map.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

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

Map::datatype Map::makeTypeInstance(const MapObjectType &type, const int id) {
    using std::make_shared;
    switch (type) {
        case CARNIVORE:
            return make_shared<Carnivore>();
        case HERBIVORE:
            return make_shared<Herbivore>();
        case FENCE:
            return std::make_shared<Fence>();
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
    for(auto it = begin(); it!=end(); it++){
        if(*it == nullptr) continue;
        auto coord = it.getCoordinate();
        if(getCoordninates(coord)->getType() != CARNIVORE) continue;
        if(!Carnivore::attemptEat()) continue;

        auto const neighbors = getNeighbors(coord);
        std::vector<Coordinate> herbivoreNeighbors;

        std::copy_if(std::begin(neighbors),
                     std::end(neighbors),
                     back_inserter(herbivoreNeighbors),
                     [&](Coordinate const & coord){
            if(getCoordninates(coord) == nullptr) return false;
            if(getCoordninates(coord)->getType() != HERBIVORE) return false;
            return true;
        });

        if(herbivoreNeighbors.empty()) continue;

        auto targetCoord = herbivoreNeighbors.at(rand() % herbivoreNeighbors.size());
        setCoordninates(targetCoord, nullptr);
    }
}

void Map::moveAll() {
    for(auto it = begin(); it!=end(); it++){
        if(*it == nullptr) continue;
        auto coord = it.getCoordinate();

        if(!getCoordninates(coord)->canMove())
            continue;

        auto const neighbors = getNeighbors(coord);

        std::vector<Coordinate> emptyNeighbors;

        std::copy_if(
                std::begin(neighbors),
                std::end(neighbors),
                back_inserter(emptyNeighbors),
                [&](Coordinate const & coord){
            return getCoordninates(coord) == nullptr;
        });

        auto targetCoord = emptyNeighbors.at(rand() % emptyNeighbors.size());
        setCoordninates(targetCoord, getCoordninates(coord));
        setCoordninates(coord, nullptr);
    }

    moveReset();
}

void Map::moveReset() {
    for(auto cell: *this){
        if(cell == nullptr) continue;
        cell->hasMovedReset();
    }
}

bool Map::isValidCoord(Coordinate &cord) const {
    return !(cord.x < 0 || cord.x >= scale || cord.y < 0 || cord.y >= scale);
}

std::vector<Coordinate> Map::getNeighbors(Coordinate const &center) const {
    std::vector<Coordinate> out;

    for(int dx=-1; dx < 2; dx++){
        for(int dy=-1; dy < 2; dy++){
            if(dx == 0 && dy == 0) continue;
            Coordinate neighbor(center.x + dx, center.y + dy);

            if(!isValidCoord(neighbor))
                continue;
            out.push_back(neighbor);
        }
    }
    return out;
}

Map::datatype &Map::getReference(Coordinate coord) {
    return map.at(coord.x).at(coord.y);
}

std::vector<Coordinate> Map::get_neighbours(const Map::Iterator &it) {
    std::vector<Coordinate> out;
    for(int x = -1; x<2;x++){
        for(int y = -1; y<2; y++){
            if(x == 0 && y == 0) continue;
            out.emplace_back(it.getCoordinate().x + x, it.getCoordinate().y + y);
        }
    }
    return out;
}


Map::Iterator &Map::Iterator::operator++() {
    coord.y++;
    if(coord.y == map.scale){
        coord.x++;
        coord.y = 0;
    }
    return *this;
}

Map::Iterator Map::Iterator::operator++(int) {
    auto temp(*this);
    ++(*this);
    return temp;
}
