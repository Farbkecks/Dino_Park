#pragma once

#include <string>
#include "MapObject.h"

class Dino : public MapObject{
public:
    Dino() = delete;
    int getId() const;
    std::string getName() const;
    void hasMovedReset() override;
    bool canMove() override;
protected:
    Dino(int id, std::string name);
    std::string getIdString() const;
    virtual std::string toText() const = 0;
    bool hasMoved;
private:
    int id;
    std::string name;
    friend std::ostream &operator<<(std::ostream &strm, const Dino &a);
};

std::ostream &operator<<(std::ostream &strm, const Dino &a);
