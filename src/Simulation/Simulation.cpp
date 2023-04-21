#include "Simulation.h"

//n*m*tMax dove n = numero cluster, m = numero leo satellite, tMax = durata totale simulazione
int N = 8;
int M = 5;
int T = 5;

int simulationTime = 24 * 60 * 60; // Durata totale della simulazione in secondi
int durataRivoluzione = 94 * 60; // Durata rivoluzione di 1 satellite in secondi
float timeSlotDuration = durataRivoluzione / M; // Intervallo durata visibilità di M satelliti in secondi
int timeSlotTotali = ceil(simulationTime / timeSlotDuration); // Numero totali timeslot
int simulationDeadline = 6 * 60 * 60; // Durata totale di un servizio in secondi
int timeSlotDeadline = ceil(simulationDeadline / timeSlotDuration); // Timeslot entro cui eseguire un servizio
int timeSlotGenerate = 0; // Timeslot inizio servizio

std::vector<Cluster> listOfClusters(){
    std::vector<Cluster> clusters;

    for(int i=0; i<N; i++){
        clusters.push_back({i});
    }

    return clusters;
};

std::vector<Service> listOfServices(){
    std::vector<Service> services;

    for(int i=0; i<N; i++){
        services.push_back({i, "AA", 10, 10});
    }

    return services;
};

Service getServiceById(std::vector<Service> listOfServices, int id){
    return listOfServices[id];
}

Solution generateSolution() {
    return Solution(timeSlotTotali);

}