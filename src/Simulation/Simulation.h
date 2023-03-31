#ifndef IOTSECURITY_SIMULATION_H
#define IOTSECURITY_SIMULATION_H

#include <cmath>

//n*m*tMax dove n = numero cluster, m = numero leo satellite, tMax = durata totale simulazione
extern int N;
extern int M;
extern int T;

extern int simulationTime; // Durata totale della simulazione in secondi
extern int durataRivoluzione; // Durata rivoluzione di 1 satellite in secondi
extern float timeSlotDuration; // Intervallo durata visibilità di M satelliti in secondi
extern int timeSlotTotali; // Numero totali timeslot
extern int simulationDeadline; // Durata totale di un servizio in secondi
extern int timeslotDeadline; // Timeslot entro cui eseguire un servizio
extern int timeslotGenerate; // Timeslot inizio richiesta

#endif //IOTSECURITY_SIMULATION_H
