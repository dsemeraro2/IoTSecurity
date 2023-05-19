#ifndef IOTSECURITY_SIMULATION_H
#define IOTSECURITY_SIMULATION_H

#include <cmath>
#include <vector>
#include "../Service/Service.h"
#include "../Cluster/Cluster.h"
#include "../Request/Request.h"
#include "../VisibilityMatrix/VisibilityMatrix.h"
#include "../Solution/Solution.h"

//n*m*tMax dove n = numero cluster, m = numero leo satellite, tMax = durata totale simulazione
extern int N;
extern int M;
extern int T;

extern int secondsAtDay; // Secondi in un giorno

extern int simulationTime; // Durata totale della simulazione in secondi
extern int durataRivoluzione; // Durata rivoluzione di 1 satellite in secondi
extern float timeSlotDuration; // Intervallo durata visibilità di M satelliti in secondi
extern int timeSlotTotali; // Numero totali timeslot
extern int simulationDeadline; // Durata totale di un servizio in secondi
extern int timeSlotDeadline; // Timeslot entro cui eseguire un servizio
extern int timeSlotGenerate; // Timeslot inizio richiesta

extern int numberEventAtDay; // Numero di eventi in un giorno


//Define the list of the differents vectors
std::vector<Cluster> initializeClusters();

std::vector<Service> initializeServices();

std::vector<Request> initializeRequests(std::vector<Service> services, int seedRand, float lambda);

Service getServiceById(std::vector<Service> listOfServices, int id);

//extern Solution generateSolution();

//Funzione obiettivo
int objectiveFunction(std::vector<Request> requests, std::vector<Service> services, Solution *solution,
                      VisibilityMatrix visibilityMatrix, bool editMode);

#endif //IOTSECURITY_SIMULATION_H
