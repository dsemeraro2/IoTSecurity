#ifndef IOTSECURITY_CONSTELLATION_H
#define IOTSECURITY_CONSTELLATION_H

#include <iostream>
#include <vector>
#include "../Satellite/Satellite.h"

class Constellation {
private:
    int mMax;
public:
    std::vector<Satellite> satellaties;

    Constellation(int mMax);
};


#endif //IOTSECURITY_CONSTELLATION_H
