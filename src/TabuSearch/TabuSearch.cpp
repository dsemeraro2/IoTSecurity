#include "TabuSearch.h"
#include "../Simulation/Simulation.h"

TabuSearch::TabuSearch(int timeSlot, int satellites, std::vector<Service> services,
                       const std::vector<Request> &requests,
                       const Solution &solution, const VisibilityMatrix &visibilityMatrix,
                       const AllocationServicesMatrix &allocationServicesMatrix) : timeSlot(timeSlot),
                                                                                   satellites(satellites),
                                                                                   services(services),
                                                                                   requests(requests),
                                                                                   solution(solution),
                                                                                   visibilityMatrix(
                                                                                           visibilityMatrix),
                                                                                   allocationServicesMatrix(
                                                                                           allocationServicesMatrix) {}

void TabuSearch::optimizationTabuSearch(int timeSlotInitial, int timeSlotTotali) {

    for (int i = timeSlotInitial; i < timeSlotTotali; i++) {

        std::vector<Request> tempRequests;

        // Ciclo su tutte le richieste
        for (int j = 0; j < requests.size(); j++) {
            // Verifico che il ts generate sia minore o uguale al timeslot corrente e che non sia gia tsDone
            if (requests[j].getTsGenerate() <= i && requests[j].getTsDone() == -1) {
                tempRequests.push_back(requests[j]);
            }
        }

        // Applicazione della swapmove
        tabuSearchIterate(tempRequests);

        // Completamento delle richieste che rispettano il tsDone
        for (int j = 0; j < tempRequests.size(); j++) {
            // Verifico che il ts generate sia minore o uguale al timeslot corrente e che non sia gia tsDone
            if (tempRequests[j].getTsDone() <= i) {
                // Riassegnazione del tempRequest completati in passato alla requests globale
                requests[tempRequests[j].getIdRequest()] = tempRequests[j];
            }
        }
    }
}

void TabuSearch::swapMove(int sourceTimeSlot, int sourceService, int sourceSatellite, int destTimeSlot,
                          int destService, int destSatellite) {

    allocationServicesMatrix.setValue(sourceTimeSlot, sourceService, sourceSatellite, 0);
    allocationServicesMatrix.setValue(destTimeSlot, destService, destSatellite, 1);
}

Solution TabuSearch::tabuSearchIterate(std::vector<Request> tempRequests) {

    Solution tempSolution = solution;
    tempSolution.f = objectiveFunction(tempRequests, services, &solution, visibilityMatrix, true);

    // Soluzione minimo
    Solution minSolution = tempSolution;

    // Ciclo su tutte le solution TODO: Check
    //for (int s = 0; s < ; s++) {

        // Esploro le soluzioni vicine
        for (int i = 0; i < timeSlot; i++) {
            for (int j = 0; j < services.size(); j++) {
                for (int k = 0; k < satellites; k++) {

                    // TODO: Da sistemare gli indici
                    swapMove(i, j, k, i, j, k);

                    // Ricalcolo della funzione obiettivo
                    tempSolution.f = objectiveFunction(tempRequests, services, &solution, visibilityMatrix, false);
                }
            }
        }

        if (tempSolution.f < minSolution.f) {
            minSolution = tempSolution;
        }
    //}

    return minSolution;
}
