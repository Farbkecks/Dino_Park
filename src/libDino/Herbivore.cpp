#include "Herbivore.h"
#include <iostream>
#include <utility>

Herbivore::Herbivore(int id, std::string name) : Dino(id, std::move(name)) {

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

