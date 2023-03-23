#include "Fence.h"
MapObjectType Fence::getType() const {
    return FENCE;
}

std::string Fence::toText() const {
    return "XXXXX";
}

bool Fence::isEdible() const {
    return false;
}

bool Fence::canMove() const {
    return false;
}

void Fence::hasMovedReset() {
}

void Fence::hasMovedLock() {
}
