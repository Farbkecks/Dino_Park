#include "Herbivore.h"
#include <iostream>

Herbivore::Herbivore(int id, std::string name) : Dino(id, name) {

}

std::string Herbivore::toText() const {
    return "H" + getIdString();
}

MapObjectType Herbivore::getType() const{
    return HERBIVORE;
}

bool Herbivore::isEdible() const {
    return true;
}

