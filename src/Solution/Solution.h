#ifndef IOTSECURITY_SOLUTION_H
#define IOTSECURITY_SOLUTION_H


#include "../Constellation/Constellation.h"

class Solution {
private:
    int timeSlot;
    std::vector<Constellation> constellations;

public:
    Solution(int timeSlot, const std::vector<Constellation> &constellation);
};


#endif //IOTSECURITY_SOLUTION_H
