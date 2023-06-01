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

Solution TabuSearch::swapMove(Solution tempSolution, int sourceTimeSlot, int sourceService, int sourceSatellite,
                              int destTimeSlot, int destService, int destSatellite) {

    Service tempService_1 = tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].getServiceByIndex(sourceService);
    Service tempService_2 = tempSolution.constellations[destTimeSlot].satellaties[destSatellite].getServiceByIndex(destService);

    if(tempService_1.getId() != -1 && tempService_2.getId() != -1){
        tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].removeServiceByIndex(sourceService);
        tempSolution.constellations[destTimeSlot].satellaties[destSatellite].removeServiceByIndex(destService);

        int checkAddServiceSource = tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].addService(
                getServiceById(this->services, destService));

        int checkAddServiceDest = tempSolution.constellations[destTimeSlot].satellaties[destSatellite].addService(
                getServiceById(this->services, sourceService));

        if(checkAddServiceSource == 1 && checkAddServiceDest == 1){
            return tempSolution;
        } else {
            tempSolution.f = INT_MAX;
            return tempSolution;
        }

        //allocationServicesMatrix.setValue(sourceTimeSlot, sourceService, sourceSatellite, 0);
        //allocationServicesMatrix.setValue(destTimeSlot, destService, destSatellite, 1);

    } else if(tempService_1.getId() != -1 && tempService_2.getId() == -1){
        tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].removeServiceByIndex(sourceService);

        int checkAddServiceSource = tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].addService(
                getServiceById(this->services, destService));

        if(checkAddServiceSource == 1){
            return tempSolution;
        } else {
            tempSolution.f = INT_MAX;
            return tempSolution;
        }
    }
}

Solution TabuSearch::tabuSearchIterate(std::vector<Request> tempRequests) {

    Solution tempSolution = solution;
    tempSolution.f = objectiveFunction(tempRequests, services, &solution, visibilityMatrix, true);

    // Soluzione minimo
    Solution minSolution = tempSolution;

    //Vettore delle soluzioni
    std::vector<float> historySolution;

    // Ciclo su tutte le solution
    while (!stopCondition(historySolution)) {

        // Esploro le soluzioni vicine
        for (int i = 0; i < timeSlot; i++) {
            for (int k = 0; k < satellites; k++) {
                int j_max = solution.constellations[i].satellaties[k].numberOfServices();

                for (int j = 0; j < j_max; j++) {
                    // Indici di arrivo
                    for (int i_2 = 0; i_2 < timeSlot; i_2++) {

                        for (int k_2 = 0; k_2 < satellites; k_2++) {

                            int j_2_max = solution.constellations[i_2].satellaties[k_2].numberOfServices() + 1;

                            for (int j_2 = 0; j_2 < j_2_max; j++) {

                                if (j_2 == j_max) {

                                } else {
                                    // Applico la swapMove
                                    swapMove(tempSolution, i, j, k, i_2, j_2, k_2);
                                }

                            }
                        }
                    }

                    // Ricalcolo della funzione obiettivo
                    tempSolution.f = objectiveFunction(tempRequests, services, &solution, visibilityMatrix, false);

                    if (tempSolution.f < minSolution.f) {
                        minSolution = tempSolution;
                    }
                }
            }
        }
        tempSolution = minSolution;
    }

    return minSolution;
}

bool TabuSearch::stopCondition(std::vector<float> historySolution) {

    if (historySolution.size() > 3)
        return true;

    return false;
}
