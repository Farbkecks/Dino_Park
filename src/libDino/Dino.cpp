#include "Dino.h"

using namespace std;

std::string Dino::getName() const{
    return this->name;
}

int Dino::getId() const{
    return this->id;
}



Dino::Dino(int id, std::string name)
:id(id), name(name)
{
    hasMovedReset();
}

std::string Dino::getIdString() const {
    string resulte{};
    if(this->id < 100) resulte +="0";
    if(this->id < 10) resulte +="0";
    resulte += std::to_string(this->id);
    return resulte;
}

void Dino::hasMovedReset() {
    hasMoved = false;
}

bool Dino::canMove()const {
    if(!hasMoved){
        return true;
    }
    return false;
}

void Dino::hasMovedLock() {
    hasMoved = true;
}
