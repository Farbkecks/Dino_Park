#include "Map.h"
#include "DinoNames.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Map::Map(const int scale, const int countCarnivore, const int countHerbivore)
: map(scale), scale(scale)
{
    srand(time(NULL));
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
                strm << cell->toText();
        }
        strm << "|\n";
    }
    for(int i=0; i<a.scale;i++)
        strm << "-----";
    strm << "--\n";

    return strm;
}


