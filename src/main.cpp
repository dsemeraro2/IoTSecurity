using namespace std;

#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"
#include "Request/Request.h"
#include "Simulation/Simulation.h"
#include "Cluster/Cluster.h"
#include "AllocationServicesMatrix/AllocationServicesMatrix.h"

Solution generateSolution() {
    return Solution(timeSlotTotali);
}

int main() {

    //cout << "\nsimulationTime: " << simulationTime << " seconds";
    //cout << "\ndurataRivoluzione: " << durataRivoluzione << " seconds";
    //cout << "\ntimeSlotDuration: " << timeSlotDuration << " seconds";
    //cout << "\ntimeSlotTotali: " << timeSlotTotali << " time slot";
    //cout << "\nsimulationDeadline: " << simulationDeadline << " seconds";
    //cout << "\ntimeslotDeadline: " << timeSlotDeadline << " time slot";

    std::vector<Cluster> clusters = listOfClusters();

    std::vector<Service> services = listOfServices();

    Solution solution = generateSolution();

    AllocationServicesMatrix allocationServicesMatrix{T,N,M};

    allocationServicesMatrix.initialize(&solution);

    return 0;
}
