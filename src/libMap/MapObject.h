#include "MapObjectType.h"
#include <string>


class MapObject{
public:
    virtual MapObjectType getType() const= 0;
    virtual std::string toText() const = 0;
    virtual bool isEdible() const = 0;
    virtual bool canMove() = 0;
    virtual void hasMovedReset() = 0;
};