#include "Carnivore.h"

Carnivore::Carnivore(int id, std::string name)
: Dino(id, name)
{
}

std::string Carnivore::toText() const {
    return "C" + getIdString();
}

MapObjectType Carnivore::getType() const{
    return CARNIVORE;
}

bool Carnivore::isEdible() const {
    return false;
}


