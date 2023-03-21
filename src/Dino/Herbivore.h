
#pragma once

#include "Dino.h"
#include <string>

class Herbivore: public Dino{
public:
    Herbivore(int id, std::string name);
private:
    friend std::ostream &operator<<(std::ostream &strm, const Herbivore &a);
};
std::ostream &operator<<(std::ostream &strm, const Herbivore &a);