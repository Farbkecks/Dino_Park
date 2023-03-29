#include "MapObject.h"

const static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

std::ostream &operator<<(std::ostream &strm, const MapObject &a)
{
    switch(a.getType()){
        case CARNIVORE: SetConsoleTextAttribute(hConsole, FOREGROUND_RED); break;
        case HERBIVORE: SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); break;
    }
    strm << a.toText();
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return strm;
}
