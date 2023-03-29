#include "Carnivore.h"

#include <utility>

Carnivore::Carnivore(int id, std::string name)
: Dino(id, std::move(name))
{
}

std::string Carnivore::toText() const {
    return "C:" + name.substr(0,1) + getIdString();
}

MapObjectType Carnivore::getType() const{
    return CARNIVORE;
}

bool Carnivore::isEdible() const {
    return false;
}

bool Carnivore::attemptEat() {
    if((rand() % 3) == 0) return true;
    return false;
}


