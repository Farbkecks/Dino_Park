#include <iostream>

enum MapObjectType{
    EMPTY,
    FENCE,
    HERBIVORE,
    CARNIVORE
};

std::ostream &operator<<(std::ostream &strm, const MapObjectType &a);