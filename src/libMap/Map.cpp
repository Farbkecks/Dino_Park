#include "Map.h"
#include "iostream"
#include <algorithm>

using namespace std;

Map::Map(int scale)
: map(scale)
{
    for(auto& inner : map)
    {
        inner.resize(scale);
    }

    setObject(1,3, make_unique<Carnivore>(3,"myCarnivore"));

    auto ptr = get(1,3);

    if(ptr != nullptr)
            cout << *ptr << endl;
    else
        cout << "is null pointer" << endl;

#if 0
    for_each(begin(map), end(map),
             [&scale](vector<datatype> & inner)
             {
                inner.resize(scale);
             });
#endif
}

void Map::setObject(const int x, const int y, shared_ptr<MapObject> obj) {
    map[x][y] = std::move(obj);
}

std::shared_ptr<MapObject> Map::get(const int x, const int y) const
{
    return map[x][y];
}


