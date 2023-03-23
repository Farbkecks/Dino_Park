#pragma once

#include "MapObjectType.h"
#include <string>


class MapObject{
public:
    virtual MapObjectType getType() const= 0;
    virtual std::string toText() const = 0;
    virtual bool isEdible() const = 0;
    virtual bool canMove() const = 0;
    virtual void hasMovedReset() = 0;
    virtual void hasMovedLock() = 0;
};

std::ostream &operator<<(std::ostream &strm, const MapObject &a);