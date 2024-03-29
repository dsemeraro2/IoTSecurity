using namespace std;

#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"
#include "Request/Request.h"
#include "Simulation/Simulation.h"
#include "Cluster/Cluster.h"
#include "AllocationServicesMatrix/AllocationServicesMatrix.h"
#include "TabuSearch/TabuSearch.h"

Solution generateSolution() {
    return Solution(timeSlotTotali);
}

int main() {

    //TODO: Da fare una simulazione ad ampio spretto sui cluster, satelliti, eventi e seed
    //n*m*tMax dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
    //int N = 8;
    //int M = 5;

    int numberEventAtDay = 6;

    int seedRand = 2;
    int slotAtDay = ceil(secondsAtDay / timeSlotDuration);
    float lambda = (numberEventAtDay / float(slotAtDay));

    std::vector<Cluster> clusters = initializeClusters();

    std::vector<Service> services = initializeServices();

    Solution solution = generateSolution();

    std::vector<Request> requests = initializeRequests(services, seedRand, lambda);

    AllocationServicesMatrix allocationServicesMatrix{T, N, M};

    //allocationServicesMatrix.initialize(&solution, services);

    VisibilityMatrix visibilityMatrix = VisibilityMatrix(T, N, M);
    visibilityMatrix.initialize();

    //std::cout << "Funzione obiettivo: " << solution.f << "\n";

    // Algoritmo di ottimizzazione
    std::cout << "Ottimizzazione:\n";
    TabuSearch tabuSearch = TabuSearch(T, M, services, requests, solution, visibilityMatrix, allocationServicesMatrix);
    tabuSearch.optimizationTabuSearch(0, T);

    return 0;
}
