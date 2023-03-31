using namespace std;

#include <iostream>
#include <cmath>

#ifndef IOTSECURITY_SIMULATION_H
#define IOTSECURITY_SIMULATION_H

//n*m*tMax dove n = numero cluster, m = numero leo satellite, tMax = durata totale simulazione
#define N 8
#define M 5
#define T 5

int simulationTime = 24 * 60 * 60; // Durata totale della simulazione in secondi
int durataRivoluzione = 94 * 60; // Durata rivoluzione di 1 satellite in secondi
float timeSlotDuration = durataRivoluzione / M; // Intervallo durata visibilità di M satelliti in secondi
int timeSlotTotali = ceil(simulationTime / timeSlotDuration); // Numero totali timeslot

int simulationDeadline = 6 * 60 * 60; // Durata totale di un servizio in secondi
int timeslotDeadline = ceil(simulationDeadline / timeSlotDuration); // Timeslot entro cui eseguire un servizio

#endif //IOTSECURITY_SIMULATION_H
