#include "Solution.h"
#include "../Simulation/Simulation.h"

Solution::Solution(int timeSlot) {
    this->timeSlot = timeSlot;
    for (int i = 0; i < timeSlot; i++) {
        Constellation constellation{M};
        this->constellations.push_back(constellation);
    }
}

/*const Constellation Solution::getConstellation(int index) const {
    return constellations[index];
}*/

/*std::vector<Solution> Solution::getTimeSlotWindow(int timeSlotInitial){
    int timeSlotEnd = timeSlotInitial + timeSlotDeadline;

    std::vector<Solution> movingWindow = { this->constellations.begin() };

    return this->constellations.
}
 */
