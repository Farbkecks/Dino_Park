#include "Carnivore.h"
#include <utility>

int Carnivore::idCount = 0;

Carnivore::Carnivore()
: Dino(idCount++, namesCarnivore[idCount])
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


