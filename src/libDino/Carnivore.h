#pragma once

#include <string>
#include "Dino.h"

class Carnivore : public Dino{
public:
    Carnivore();
    MapObjectType getType()const override;
    bool isEdible() const override;
    static bool attemptEat();
private:
    std::string toText() const override;
    static int idCount;
};
