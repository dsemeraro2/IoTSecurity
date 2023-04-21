#ifndef IOTSECURITY_SOLUTION_H
#define IOTSECURITY_SOLUTION_H


#include "../Constellation/Constellation.h"
#include "../Simulation/Simulation.h"

class Solution {
private:
    int timeSlot;

public:
    std::vector<Constellation> constellations;
    Solution(int timeSlot);
    const Constellation getConstellation(int index) const;
    //std::vector<Solution> getTimeSlotWindow(int timeSlotInitial);
};


#endif //IOTSECURITY_SOLUTION_H
