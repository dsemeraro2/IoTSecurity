#include "TabuSearch.h"

TabuSearch::TabuSearch() {}

void TabuSearch::swapMove(Solution *solution, int timeSlotSize, int satellitesSize, int servicesSize) {

    for (int i = 0; i < timeSlotSize; i++) {

        for (int j = 0; j < servicesSize; j++) {

            for (int k = 0; k < satellitesSize; k++) {

            }
        }
    }
}

void TabuSearch::optimizationTabuSearch(std::vector<Request> requests, int timeSlotInitial, int timeSlotTotali) {

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


