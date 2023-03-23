#include "MapObject.h"


std::ostream &operator<<(std::ostream &strm, const MapObject &a)
{
    return strm << a.toText();
}
