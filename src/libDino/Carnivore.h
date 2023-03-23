#pragma once

#include <string>
#include "Dino.h"

class Carnivore : public Dino{
public:
    Carnivore(int id, std::string name);
    MapObjectType getType() override;
    bool isEdible() const override;
    bool canMove() override;
private:
    std::string toText() const override;
};
