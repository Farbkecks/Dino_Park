#include <iostream>
#include "Map.h"

using namespace std;

int gameloop(Map & map){
    int days = 0;
    while(map.hasHerbivore()){
        days++;
        cout << map << endl;
        map.eating();
        map.moving();
    }
}

int main() {
    srand(time(NULL));
    Map map(20, 5,20);
    gameloop(map);
    return 0;
}