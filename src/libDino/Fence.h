#pragma once

#include "MapObjectType.h"
#include "MapObject.h"

class Fence : public MapObject{
public:
    MapObjectType getType() const override;

    std::string toText() const override;

    bool isEdible() const override;

    bool canMove() const override;

    void hasMovedReset() override;

    void hasMovedLock() override;
};
