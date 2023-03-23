#include "MapObjectType.h"

std::ostream &operator<<(std::ostream &strm, const MapObjectType &a){
    switch (a) {
        case EMPTY: return strm << "EMPTY"; break;
        case FENCE: return strm << "DENCE"; break;
        case HERBIVORE: return strm << "HERBIVORE"; break;
        case CARNIVORE: return strm << "CARNIVORE"; break;
    }
    strm << "Test";
}
