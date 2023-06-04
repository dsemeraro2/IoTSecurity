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
        Solution tempSolution = tabuSearchIterate(tempRequests);

        //TODO DA ASSEGNARE IL TSDONE è un ciclo in quanto va per tutte le richieste
        // SIMILE ALLA FUNZIONE OBIETTIVO CAMBIANDO IL LIMETE TEMPORALE CHE CORRISPONDE AD I

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

    Service tempService_1 = tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].getServiceByIndex(
            sourceService);
    Service tempService_2 = tempSolution.constellations[destTimeSlot].satellaties[destSatellite].getServiceByIndex(
            destService);

    if (tempService_1.getId() != -1 && tempService_2.getId() != -1) {
        tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].removeServiceByIndex(sourceService);
        tempSolution.constellations[destTimeSlot].satellaties[destSatellite].removeServiceByIndex(destService);

        int checkAddServiceSource = tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].addService(
                getServiceById(this->services, destService));

        int checkAddServiceDest = tempSolution.constellations[destTimeSlot].satellaties[destSatellite].addService(
                getServiceById(this->services, sourceService));

        if (checkAddServiceSource == 1 && checkAddServiceDest == 1) {
            return tempSolution;
        } else {
            tempSolution.f = INT_MAX;
            return tempSolution;
        }

        //allocationServicesMatrix.setValue(sourceTimeSlot, sourceService, sourceSatellite, 0);
        //allocationServicesMatrix.setValue(destTimeSlot, destService, destSatellite, 1);

    } else if (tempService_1.getId() != -1 && tempService_2.getId() == -1) {
        tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].removeServiceByIndex(sourceService);

        int checkAddServiceSource = tempSolution.constellations[sourceTimeSlot].satellaties[sourceSatellite].addService(
                getServiceById(this->services, destService));

        if (checkAddServiceSource == 1) {
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

        int minInteraction = INT_MAX;

        Solution solutionSwapped = tempSolution;
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

                                // Applico la swapMove
                                solutionSwapped = swapMove(tempSolution, i, j, k, i_2, j_2, k_2);
                                if (solutionSwapped.f != INT_MAX) {
                                    // Ricalcolo della funzione obiettivo
                                    solutionSwapped.f = objectiveFunction(tempRequests, services, &solutionSwapped,
                                                                          visibilityMatrix, false);
                                    if (solutionSwapped.f != INT_MAX) {
                                        if (solutionSwapped.f < minInteraction) {
                                            //TODO: FARE IL CONTROLLO CHE LA MINSOLUTION.F NON SIA GIA PRESENTE NELLA TABULIST

                                            /* TODO TO CHECK se è okay
                                            if(!isSolutionInTabuList(solutionSwapped)){
                                                minInteraction = minSolution.f;
                                                minSolution = solutionSwapped;
                                            }*/

                                            minInteraction = minSolution.f;
                                            minSolution = solutionSwapped;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        this->tabuList.push_back(minSolution);
        tempSolution = minSolution;
        std::cout << "tempSolution.f: " << tempSolution.f;
    }
    return minSolution;
}

bool TabuSearch::stopCondition(std::vector<float> historySolution) {

    //TODO DEFINIRE LA STOP CONDITION MEGLIO
    if (historySolution.size() > 3)
        return true;

    return false;
}

bool TabuSearch::isSolutionInTabuList(Solution &sourceSol) {

    for (Solution& solution : this->tabuList) {
        if (solution.f == sourceSol.f) {
            return true;  // f è gia presente
        }
    }

    return false;
}

bool TabuSearch::compareSolution(Solution &sourceSol, Solution &destSol) { // Li passo per referenza e non per copia

    // Confronta il valore di f
    if (sourceSol.f != destSol.f) {
        return false;
    }

    // Confronta il numero di costellazioni
    if (sourceSol.constellations.size() != destSol.constellations.size()) {
        return false;
    }

    // Confronta ogni costellazione
    for (int i = 0; i < sourceSol.constellations.size(); ++i) {
        const Constellation &sourceConstellation = sourceSol.constellations[i];
        const Constellation &destConstellation = destSol.constellations[i];

        // Confronta il numero di satelliti nella costellazione
        if (sourceConstellation.satellaties.size() != destConstellation.satellaties.size()) {
            return false;
        }

        // Confronta ogni satellite
        for (int j = 0; j < sourceConstellation.satellaties.size(); ++j) {
            Satellite sourceSatellite = sourceConstellation.satellaties[j];
            Satellite destSatellite = destConstellation.satellaties[j];

            // Confronta l'ID del satellite
            if (sourceSatellite.getId() != destSatellite.getId()) {
                return false;
            }

            // Confronta il numero di servizi del satellite
            if (sourceSatellite.numberOfServices() != destSatellite.numberOfServices()) {
                return false;
            }

            // Confronta ogni servizio del satellite
            for (int k = 0; k < sourceSatellite.numberOfServices(); ++k) {
                const Service &sourceService = sourceSatellite.getServiceByIndex(k);
                const Service &destService = destSatellite.getServiceByIndex(k);

                // Confronta l'ID del servizio
                if (sourceService.getId() != destService.getId()) {
                    return false;
                }

                // Confronta l'utilizzo di CPU e RAM del servizio
                if (sourceService.getCpuUsed() != destService.getCpuUsed() ||
                    sourceService.getRamUsed() != destService.getRamUsed()) {
                    return false;
                }
            }

            // Confronta l'utilizzo di CPU e RAM del satellite
            if (sourceSatellite.getCpuUsed() != destSatellite.getCpuUsed() ||
                sourceSatellite.getRamUsed() != destSatellite.getRamUsed()) {
                return false;
            }
        }
    }

    return true;
}

