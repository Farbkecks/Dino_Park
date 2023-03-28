#include <iostream>
#include "Map.h"

using namespace std;

int gameloop(Map map){
    int days = 0;
    while(map.hasHerbivore()){
        cout << map << endl;
    }
}

int main() {
    Map map(20, 5,20);
    gameloop(map);
    return 0;
}