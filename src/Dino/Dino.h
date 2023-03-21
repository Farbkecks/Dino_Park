
#pragma once

#include <string>

class Dino {
public:
    Dino() = delete;
    int getId() const;
    std::string getName() const;
protected:
    Dino(int id, std::string name);
//private:
    int id;
    std::string name;
    friend std::ostream &operator<<(std::ostream &strm, const Dino &a);
};

std::ostream &operator<<(std::ostream &strm, const Dino &a);
