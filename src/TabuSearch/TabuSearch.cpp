#include "TabuSearch.h"
#include "../Simulation/Simulation.h"

TabuSearch::TabuSearch(int timeSlot, int satellites, std::vector<Service> services,
                       const std::vector<Request> &requests,
                       const Solution &solution, const VisibilityMatrix &visibilityMatrix,
                       const AllocationServicesMatrix &allocationServicesMatrix) : services(services),
                                                                                   requests(requests),
                                                                                   solution(solution),
                                                                                   visibilityMatrix(
                                                                                           visibilityMatrix),
                                                                                   allocationServicesMatrix(
                                                                                           allocationServicesMatrix) {
    this->timeSlot = timeSlot;
    this->satellites = satellites;
    this->services = services;
    this->requests = requests;
    this->solution = solution;
    this->visibilityMatrix = visibilityMatrix;
    this->allocationServicesMatrix = allocationServicesMatrix;

}


void saveFValueToFile(std::vector<float> fValue, const std::string &filename) {
    std::ofstream file(filename, std::ios::app);

    if (file.is_open()) {
        for(int i =0; i<fValue.size(); i++){
            file << fValue[i] << "\n";
        }
        file.close();
        std::cout << "Valore di f salvato correttamente su file: " << filename << "\n";
    } else {
        std::cout << "Impossibile aprire il file: " << filename << "\n";
    }
}

void TabuSearch::optimizationTabuSearch(int timeSlotInitial, int timeSlotTotali) {

    std::vector<float> vectorF;

    for (int i = timeSlotInitial; i < timeSlotTotali; i++) {

        std::vector<Request> tempRequests;

        // Ciclo su tutte le richieste
        for (int j = 0; j < requests.size(); j++) {
            // Verifico che il ts generate sia minore o uguale al timeslot corrente e che non sia gia tsDone
            if (requests[j].getTsGenerate() <= i && requests[j].getTsDone() == -1) {
                //TODO CHECK se funziona la condizione
                tempRequests.push_back(requests[j]);
            }
        }

        // Applicazione della swapmove
        if (tempRequests.size() > 0) {

            Solution tempSolution = tabuSearchIterate(tempRequests);

            filterTsDone(requests, services, &tempSolution, visibilityMatrix, false, i);

            // Completamento delle richieste che rispettano il tsDone
            /*for (int j = 0; j < tempRequests.size(); j++) {
                // Verifico che il ts generate sia minore o uguale al timeslot corrente e che non sia gia tsDone
                if (tempRequests[j].getTsDone() <= i) {
                    // Riassegnazione del tempRequest completati in passato alla requests globale
                    requests[tempRequests[j].getIdRequest()] = tempRequests[j];
                }
            }*/

            solution = tempSolution;

            //TODO SALVARE SU FILE SOLUTION.F -- DA VERIFICARE CHE F VENGA VALORIZZATO


            vectorF.push_back(tempSolution.f);

        } else {
            std::cout << "Nessuna richiesta trovata!";
        }
    }

    // Salvataggio f dopo l'ottimizzazione
    for(int i=0; i<vectorF.size(); i++){
        std::string fAfterFilename = "f_after.txt";
        saveFValueToFile(vectorF, fAfterFilename);
    }
}

Solution TabuSearch::swapMove(Solution tempSolution, int sourceTimeSlot, int sourceService, int sourceSatellite,
                              int destTimeSlot, int destService, int destSatellite) {

    std::cout<<"Swap move...\n";

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

    return tempSolution;
}

Solution TabuSearch::tabuSearchIterate(std::vector<Request> tempRequests) {

    // Mi ripulisco la tabuList per ogni oggetto di Solution
    tabuList.clear();

    Solution tempSolution = solution;

    tempSolution.f = objectiveFunction(tempRequests, services, &solution, visibilityMatrix, true);

    // Salvataggio f dopo l'ottimizzazione
    //std::string fAfterFilename = "f_after.txt";
    //saveFValueToFile(tempSolution.f, fAfterFilename);

    this->solution = tempSolution;
    //TODO VERIFICARE CHE NELLA CREAZIONE SE ESCE UNA SOLUTIONE INFINITO, NELLA PRIMA SOLUTION

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
                                std::cout<<"...\n";
                                // Applico la swapMove
                                solutionSwapped = swapMove(tempSolution, i, j, k, i_2, j_2, k_2);
                                if (solutionSwapped.f != INT_MAX) {
                                    // Ricalcolo della funzione obiettivo
                                    solutionSwapped.f = objectiveFunction(tempRequests, services, &solutionSwapped,
                                                                          visibilityMatrix, false);
                                    if (solutionSwapped.f != INT_MAX) {
                                        if (solutionSwapped.f < minInteraction) {

                                            if (!isSolutionInTabuList(solutionSwapped)) {
                                                minInteraction = minSolution.f;
                                                minSolution = solutionSwapped;
                                            }
                                            //TODO GESTIRE CASO UNFEASIBLE
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        std::cout << "MinSolution added in TabuList: " << minSolution.f << "\n";

        //TODO Prendere la migliore soluzione di tutta la tabusearch iterate
        if(tabuList.size() > 0){
            Solution bestSolution = tabuList[0];
            for (const Solution& solution : tabuList) {
                if (bestSolution.f >= solution.f) {
                    bestSolution = solution;
                }
            }
            std::cout<< "Best f solution:"<< bestSolution.f << "\n";
        }

        this->tabuList.push_back(minSolution);
        tempSolution = minSolution;
        //std::cout << "tempSolution.f: " << tempSolution.f << "\n";
        historySolution.push_back(tempSolution.f);

    }
    return minSolution;
}

bool TabuSearch::stopCondition(std::vector<float> historySolution) {

    //TODO DEFINIRE LA STOP CONDITION MEGLIO
    if (historySolution.size() > 300) {
        std::cout << "\nStopping condition TRUE\n";
        return true;
    }
    return false;
}

bool TabuSearch::isSolutionInTabuList(Solution &sourceSol) {

    int count = 0;
    for (Solution &destSol: this->tabuList) {
        if (!compareSolution(sourceSol, destSol)) {
            count++;
        }
    }

    if (count == tabuList.size()) {
        return true;
    } else {
        return false;
    }

}

bool TabuSearch::compareSolution(const Solution &sourceSol, const Solution &destSol) { // Li passo per referenza e non per copia

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

void TabuSearch::filterTsDone(std::vector<Request> &requests, std::vector<Service> services, Solution *solution,
                              VisibilityMatrix visibilityMatrix, bool editMode, int currentTimeSlot) {

    std::cout << "Request size: " << requests.size() << "\n";
    bool serviceDeployed = false;

    // i numero delle richieste
    for (int i = 0; i < requests.size(); i++) {

        serviceDeployed = false;

        Service tempService = getServiceById(services, requests[i].getIdService());

        int delayRequestCollection = 1; //Delay della raccolta del servizio verso i satelliti, 1 timeslot
        int delayRequestOptimization = 2; //Delay della ottimizzazione + deploy del servizio, 2 timeslot (contenente l'elaborazione + il deploy)

        int initialTimeSlot = requests[i].getTsGenerate();
        int deadlineTimeSlot = requests[i].getTsDeadline();

        if (tempService.getId() != -1) {

            //j numero della deadlineTimeSlot del singolo servizio DOVREBBE ESSERE IL MASSIMO
            for (int j = initialTimeSlot + delayRequestCollection + delayRequestOptimization;
                 j < deadlineTimeSlot; j++) {

                //k numero dei satelliti
                for (int k = 0; k < solution->constellations[j].satellaties.size(); k++) {

                    std::vector<Service> listServicesSatellite = solution->constellations[j].satellaties[k].getServices();

                    //m Numero dei diversi servizi del satellite
                    for (int m = 0; m < listServicesSatellite.size(); m++) {

                        if (listServicesSatellite[m].getId() == tempService.getId()) {
                            if (visibilityMatrix.getValue(j, tempService.getId(), k) == 1) {

                                serviceDeployed = true;
                                // Verifico che il timeSlot di completamento deve essere minore al timeSlot attuale
                                if (initialTimeSlot + j <= currentTimeSlot) {
                                    requests[i].setTsDone(initialTimeSlot + j);

                                    std::cout << "Request done ";
                                }
                                break;
                            }
                        }
                    }
                    if (serviceDeployed) break;
                }
                if (serviceDeployed) break;
            }
        }
    }
}

bool TabuSearch::compareBestSolution(const Solution& sourceSol, const Solution& destSol) {
    if (sourceSol.f < destSol.f) {
        return true;  // La seconda soluzione è migliore della prima
    } else {
        return false; // La prima soluzione è migliore della seconda
    }
}
