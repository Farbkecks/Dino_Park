
#pragma once

#include "Dino.h"
#include <string>

class Herbivore: public Dino{
public:
    Herbivore();
    MapObjectType getType() const override;
    bool isEdible() const override;

private:
    std::string toText() const override;
    static int idCount;
};