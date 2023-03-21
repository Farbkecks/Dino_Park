#include "Herbivore.h"

Herbivore::Herbivore(int id, std::string name) : Dino(id, name) {

}

std::ostream &operator<<(std::ostream &strm, const Herbivore &a) {
    return strm << a.id;
}
