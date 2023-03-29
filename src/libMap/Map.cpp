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

void Map::setObject(const int x, const int y, shared_ptr<MapObject> const obj) {
    if(map[x][y] != nullptr){
        throw std::invalid_argument("place is not empty");
    }
    map[x][y] = obj;
}

Map::datatype Map::getCoordninates(const int x, const int y) const {
    return map[x][y];
}

Map::datatype Map::getCoordninates(const Coordinate coord) const {
    return getCoordninates(coord.x, coord.y);
}

void Map::setCoordninates(Coordinate const coord, Map::datatype obj)
{
    map.at(coord.x).at(coord.y) = obj;
}

void Map::addTypeBulk(const MapObjectType &type, const int count) {
    for(int i = 0 ; i<count; i++){
        int x,y;
        do { // loop until an empty place is found
            x = Map::random0To20();
            y = Map::random0To20();
        } while(getCoordninates(x,y) != nullptr);

        setObject(x,y, Map::makeTypeInstance(type, i));
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

unsigned int Map::countType(const MapObjectType type) const {
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
    walk([&](int x, int y){eat(x,y);});
}

void Map::eat(const int x, const int y) {

    if(getCoordninates(x,y) == nullptr) return;
    if(getCoordninates(x,y)->getType() != CARNIVORE) return;
    if(!Carnivore::attemptEat()) return;

    for(int l=-1; l<2;l++){
        for(int k=-1; k<2;k++){
            if(l==0 && k==0) continue;
            int newX = x+l;
            int newY = y+k;
            if(newX < 0 || newX > 19) continue;
            if(newY < 0 || newY > 19) continue;
            if(map[newX][newY] == nullptr) continue;
            if(map[newX][newY]->getType() != HERBIVORE) continue;
            map[newX][newY] = nullptr;
            return;
        }
    }
}

void Map::moveAll() {
    walk([&](int x, int y){move(x,y);});

    moveReset();
}

void Map::move(const int x, const int y) {
    if(!getCoordninates(x,y)->canMove())
        return;

    auto const neighbors = getNeighbors(Coordinate(x,y));

    vector<Coordinate> emptyNeighbors;

    std::copy_if(begin(neighbors), end(neighbors), back_inserter(emptyNeighbors), [&](Coordinate const & coord){
        return getCoordninates(coord) == nullptr;
    });

    auto targetCoord = emptyNeighbors.at(rand() % emptyNeighbors.size());
    setCoordninates(targetCoord, getCoordninates(x,y));
    setCoordninates(Coordinate(x,y), nullptr);
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





