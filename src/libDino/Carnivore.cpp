#include "Carnivore.h"

Carnivore::Carnivore(int id, std::string name)
: Dino(id, name)
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


