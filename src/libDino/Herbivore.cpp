#include "Herbivore.h"
#include <iostream>
#include <utility>

int Herbivore::idCount = 0;

Herbivore::Herbivore() : Dino(idCount++, namesCarnivore[idCount]) {

}

std::string Herbivore::toText() const {
    return "H:" + name.substr(0,1) + getIdString();
}

MapObjectType Herbivore::getType() const{
    return HERBIVORE;
}

bool Herbivore::isEdible() const {
    return true;
}

