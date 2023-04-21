using namespace std;

#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"
#include "Request/Request.h"
#include "Simulation/Simulation.h"

int main() {

    //cout << "\nsimulationTime: " << simulationTime << " seconds";
    //cout << "\ndurataRivoluzione: " << durataRivoluzione << " seconds";
    //cout << "\ntimeSlotDuration: " << timeSlotDuration << " seconds";
    cout << "\ntimeSlotTotali: " << timeSlotTotali << " time slot";
    //cout << "\nsimulationDeadline: " << simulationDeadline << " seconds";
    cout << "\ntimeslotDeadline: " << timeSlotDeadline << " time slot";



    /*
    std::vector<Request> requests;

    for (int i = 0; i < 10; i++) {
        requests.insert(requests.end(), {i, 0, 1, -1});
    }

    for (int i = 0; i < 10; i++) {
        std::cout<<"\nRequest: " << requests[i].getId();
    }

    /*
    VisibilityMatrix matrix(timeSlotTotali,N,M);
    matrix.setValue(0,0,0,1);
    matrix.initialize();
    matrix.showMatrix();
    */

    return 0;
}
