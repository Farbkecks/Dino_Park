#pragma once

#include <string>
#include "Dino.h"

class Carnivore : public Dino{
public:
    Carnivore(int id, std::string name);
    MapObjectType getType()const override;
    bool isEdible() const override;
private:
    std::string toText() const override;
};
