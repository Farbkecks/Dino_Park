#include "Map.h"
#include "iostream"

using namespace std;

Map::Map(int scale, int car, int her) {
    MapObject* map[scale][scale];
    Carnivore a(4,"Test");
    map[3][4] = &a;
    cout << *map[3][4] << endl;
//    cout << ((Carnivore) *map[3][4]) << endl;
}
