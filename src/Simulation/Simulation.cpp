#include "Simulation.h"
#include "../VisibilityMatrix/VisibilityMatrix.h"

int simulationTime = 24 * 60 * 60; // Durata totale della simulazione in secondi
int durataRivoluzione = 94 * 60; // Durata rivoluzione di 1 satellite in secondi
float timeSlotDuration = durataRivoluzione / M; // Intervallo durata visibilità di M satelliti in secondi
int timeSlotTotali = ceil(simulationTime / timeSlotDuration); // Numero totali timeslot
int simulationDeadline = 6 * 60 * 60; // Durata totale di un servizio in secondi
int timeSlotDeadline = ceil(simulationDeadline / timeSlotDuration); // Timeslot entro cui eseguire un servizio

//n*m*tMax dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
int N = 8;
int M = 5;
int T = timeSlotTotali;

std::vector<Cluster> initializeClusters() {
    std::vector<Cluster> clusters;
    for (int i = 0; i < N; i++) {
        clusters.push_back({i});
    }
    return clusters;
};

std::vector<Service> initializeServices() {
    std::vector<Service> services;
    for (int i = 0; i < N; i++) {
        services.push_back({i, "AA", 10, 10});
    }
    return services;
};

std::vector<Request> initializeRequests(std::vector<Service> services) {
    std::vector<Request> requests;
    int sizeService = services.size();
    for (int i = 0; i < 10; i++) {
        //std::cout<<"i:"<<i<<"i%sizeService:"<<i%sizeService<<"\n";
        requests.insert(requests.end(), {i, 0, i + timeSlotDeadline, -1, i % sizeService});
    }
    return requests;
}

Service getServiceById(std::vector<Service> listOfServices, int id) {
    Service tempServizio = Service(-1, "", 0, 0);
    for (int i = 0; i < listOfServices.size(); i++) {
        if (listOfServices[i].getId() == id)
            tempServizio = listOfServices[id];
    }
    return tempServizio;
}

int objectiveFunction(std::vector<Request> requests, std::vector<Service> services, Solution solution,
                      VisibilityMatrix visibilityMatrix) {

    std::cout << requests.size() << "\n";
    int f = 0; //Ritardo da minimizzare
    bool serviceDeployed = false;

    //i numero delle richieste
    for (int i = 0; i < requests.size(); i++) {

        serviceDeployed = false;
        //std::cout << "i:" << i << "\n";

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
                for (int k = 0; k < solution.constellations[j].satellaties.size(); k++) {

                    std::vector<Service> listServicesSatellite = solution.constellations[j].satellaties[k].getServices();

                    std::cout << "i: " << i << " j: " << j << " k: " << k << "\n";
                    //m Numero dei diversi servizi del satellite
                    for (int m = 0; m < listServicesSatellite.size(); m++) {

                        if (listServicesSatellite[m].getId() == tempService.getId()) {
                            if (visibilityMatrix(j, tempService.getId(), k) == 1) {
                                serviceDeployed = true;
                                f = f + (j - initialTimeSlot);
                                std::cout << "f = " << f << "\n";
                                break;
                            }
                        }
                    }
                    if (serviceDeployed) {
                        break;
                    }
                }
                if (serviceDeployed) break;
            }
        } else {
            std::cout << "Errore Servizio non trovato! " << requests[i].getId() << "\n";
        }
        if (!serviceDeployed) {
            return 63550;
        }
    }
    return f;
}
