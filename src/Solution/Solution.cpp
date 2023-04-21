#include "Solution.h"

Solution::Solution(int timeSlot, const std::vector<Constellation> &constellations) {
    this->timeSlot = timeSlot;
    this->constellations = constellations;
}

const Constellation Solution::getConstellation(int index) const {
    return constellations[index];
}

/*std::vector<Solution> Solution::getTimeSlotWindow(int timeSlotInitial){
    int timeSlotEnd = timeSlotInitial + timeSlotDeadline;

    std::vector<Solution> movingWindow = { this->constellations.begin() };

    return this->constellations.
}
 */
