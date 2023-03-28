#include "Map.h"
#include "DinoNames.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>


using namespace std;

Map::Map(const int scale, const int countCarnivore, const int countHerbivore)
: map(scale), scale(scale)
{
    for(auto& inner : map)
    {
        inner.resize(scale);
    }

    int countFence = scale * scale * 0.1;
    addTypeBulk(FENCE, countFence);
    addTypeBulk(CARNIVORE, countCarnivore);
    addTypeBulk(HERBIVORE, countHerbivore);
}

void Map::setObject(const int x, const int y, shared_ptr<MapObject> obj) {
    if(map[x][y] != nullptr){
        throw 1;
    }
    map[x][y] = std::move(obj);
}

std::shared_ptr<MapObject> Map::getCoordninates(const int x, const int y) const {
    return map[x][y];
}

void Map::addTypeBulk(const MapObjectType &type, const int count) {
    for(int i = 0 ; i<count; i++){
        int x,y;
        while (true){
            x = randrom0To20();
            y = randrom0To20();
            try{
                addType(x,y,type, i);
            } catch (int e){
                continue;
            }
            break;
        }
    }
}

void Map::addType(const int x, const int y, const MapObjectType &type, const int id) {
    switch (type) {
        case CARNIVORE:
            setObject(x,y, make_unique<Carnivore>(id, namesCarnivore[id])); break;
        case HERBIVORE:
            setObject(x,y, make_unique<Herbivore>(id, namesHerbivore[id])); break;
        case FENCE:
            setObject(x,y, make_unique<Fence>()); break;
    }
}

int Map::randrom0To20() const {
    return rand() % 20;
}

std::ostream &operator<<(std::ostream &strm, const Map &a){
    for(int i=0; i<a.scale;i++)
        strm << "-----";
    strm << "--\n";
    for(auto row: a.map){
        strm << "|";
        for(auto cell: row){
            if(cell == nullptr)
                strm << "     ";
            else
                strm << *cell;
        }
        strm << "|\n";
    }
    for(int i=0; i<a.scale;i++)
        strm << "-----";
    strm << "--\n";

    return strm;
}

MapObjectType Map::checkCoordinates(const int x, const int y) const {
    if(map[x][y] == nullptr) return EMPTY;
    return map[x][y]->getType();
}

bool Map::hasHerbivore() const {
    for(auto const & row: map){
        for(auto const & cell: row){
            if(cell == nullptr) continue;
            if(cell->getType() == HERBIVORE) return true;
        }
    }
    return false;
}

void Map::eating() {
    for(int i=0; i<scale;i++){
        for(int y=0; y<scale; y++){
            if(map[i][y] == nullptr) continue;
            if(map[i][y]->getType() != CARNIVORE) continue;
            if(!Carnivore::attemptEat()) continue;
            eat(i,y);
        }
    }
}

void Map::eat(const int x, const int y) {
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

void Map::moving() {
    for(int i=0; i<scale;i++){
        for(int y=0; y<scale; y++){
            if(map[i][y] == nullptr) continue;
            if(!map[i][y]->canMove()) continue;
            move(i,y);
        }
    }
}

void Map::move(const int x, const int y) {
    int random = rand() % 8;
    int count = 0;
    for(int l=-1; l<2;l++){
        for(int k=-1; k<2;k++){
            if(l==0 && k==0) continue;
            if(count++ != random) continue;
            int newX = x+l;
            int newY = y+k;
            if(newX < 0 || newX > 19) continue;
            if(newY < 0 || newY > 19) continue;
            if(map[newX][newY] != nullptr) continue;
            map[newX][newY] = std::move(map[x][y]);
            map[newX][newY]->hasMovedLock();
            return;
        }
    }
}

void Map::moveReset() {
    for(auto const & row: map){
        for(auto const & cell: row){
            if(cell == nullptr) continue;
            cell->hasMovedReset();
        }
    }
}





