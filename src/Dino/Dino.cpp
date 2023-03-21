#include "Dino.h"

std::string Dino::getName() const{
    return this->name;
}

int Dino::getId() const{
    return this->id;
}

std::ostream &operator<<(std::ostream &strm, const Dino &a)
{
    return strm << std::to_string(a.id);
}

Dino::Dino(int id, std::string name)
:id(id), name(name)
{
}


