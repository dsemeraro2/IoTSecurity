#ifndef IOTSECURITY_SOLUTION_H
#define IOTSECURITY_SOLUTION_H


#include "../Constellation/Constellation.h"

class Solution {
private:
    int timeSlot;

public:

    int f;
    std::vector<Constellation> constellations;

    Solution(int timeSlot);
    //const Constellation getConstellation(int index) const;
    //std::vector<Solution> getTimeSlotWindow(int timeSlotInitial);
};


#endif //IOTSECURITY_SOLUTION_H
