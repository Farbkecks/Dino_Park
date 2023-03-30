#include <iostream>
#include <chrono>
#include <thread>
#include "Map.h"

using namespace std;

void gameloop(Map & map){
    int days = 0;
    while(map.countType(HERBIVORE)){
        days++;
        cout << map << endl;
        map.eatAll();
        map.moveAll();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    cout << map << endl;
    cout << "hat " << days << " Tage gedauert" << endl;
}

int main() {
    srand(time(nullptr));

    Map map(20, 5,20);
    gameloop(map);
    return 0;
}