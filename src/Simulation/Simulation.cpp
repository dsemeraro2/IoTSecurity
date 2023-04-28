#include "Simulation.h"

//n*m*tMax dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
int N = 8;
int M = 5;
int T = 5;

int simulationTime = 24 * 60 * 60; // Durata totale della simulazione in secondi
int durataRivoluzione = 94 * 60; // Durata rivoluzione di 1 satellite in secondi
float timeSlotDuration = durataRivoluzione / M; // Intervallo durata visibilità di M satelliti in secondi
int timeSlotTotali = ceil(simulationTime / timeSlotDuration); // Numero totali timeslot
int simulationDeadline = 6 * 60 * 60; // Durata totale di un servizio in secondi
int timeSlotDeadline = ceil(simulationDeadline / timeSlotDuration); // Timeslot entro cui eseguire un servizio

std::vector<Cluster> initializeClusters(){
    std::vector<Cluster> clusters;

    for(int i=0; i<N; i++){
        clusters.push_back({i});
    }

    return clusters;
};

std::vector<Service> initializeServices(){
    std::vector<Service> services;

    for(int i=0; i<N; i++){
        services.push_back({i, "AA", 10, 10});
    }

    return services;
};

std::vector<Request> initializeRequests(){
    std::vector<Request> requests;
    for (int i = 0; i < 10; i++) {
        requests.insert(requests.end(), {i, i, i + timeSlotDeadline, -1, i});
    }
    return requests;
}

Service getServiceById(std::vector<Service> listOfServices, int id){
    return listOfServices[id];
}
