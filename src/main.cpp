using namespace std;

#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"
#include "Request/Request.h"
#include "Simulation/Simulation.h"
#include "Cluster/Cluster.h"

int main() {

    //cout << "\nsimulationTime: " << simulationTime << " seconds";
    //cout << "\ndurataRivoluzione: " << durataRivoluzione << " seconds";
    //cout << "\ntimeSlotDuration: " << timeSlotDuration << " seconds";
    //cout << "\ntimeSlotTotali: " << timeSlotTotali << " time slot";
    //cout << "\nsimulationDeadline: " << simulationDeadline << " seconds";
    //cout << "\ntimeslotDeadline: " << timeSlotDeadline << " time slot";

    std::vector<Cluster> clusters = listOfCluster();

    return 0;
}
