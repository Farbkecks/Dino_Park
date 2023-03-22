
#pragma once

#include "Dino.h"
#include <string>

class Herbivore: public Dino{
public:
    Herbivore(int id, std::string name);
private:
    std::string toText() const override;
};