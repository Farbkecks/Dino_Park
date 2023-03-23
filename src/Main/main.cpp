#include <iostream>
#include "Herbivore.h"
#include "Carnivore.h"


int main() {
    using namespace std;


    Carnivore a(17, "Test");
    cout << a.getType() << endl;
    cout << a.canMove() << endl;
    cout << a.canMove() << endl;
    a.hasMovedReset();
    cout << a.canMove() << endl;
    cout << a << endl;

    return 0;
}