#ifndef IOTSECURITY_SOLUTION_H
#define IOTSECURITY_SOLUTION_H


#include "../Constellation/Constellation.h"
#include "../Simulation/Simulation.h"

class Solution {
private:
    int timeSlot;
    std::vector<Constellation> constellations;

public:
    Solution(int timeSlot, const std::vector<Constellation> &constellation);
    //std::vector<Solution> getTimeSlotWindow(int timeSlotInitial);
};


#endif //IOTSECURITY_SOLUTION_H
