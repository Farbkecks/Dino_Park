#include "MapObject.h"

//template<typename Base, typename T>
//inline bool instanceof(const T *ptr) {
//    return dynamic_cast<const Base*>(ptr) != nullptr;
//}

std::ostream &operator<<(std::ostream &strm, const MapObject &a)
{
//    cout << instanceof<Carnivore>(a) << endl;

    return strm << a.toText();
}
