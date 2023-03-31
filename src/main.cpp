using namespace std;
#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"
#include "Request/Request.h"

//n*m*tMax dove n = numero cluster, m = numero leo satellite, tMax = durata totale simulazione
#define N 8
#define M 5
#define T 5

int main()
{
    int simulationTime = 24 * 60 * 60; // Durata totale della simulazione in secondi
    int durataRivoluzione = 94 * 60; // Durata rivoluzione di 1 satellite in secondi
    float timeSlotDuration = durataRivoluzione / M; // Intervallo durata visibilità di M satelliti in secondi
    int timeSlotTotali = ceil(simulationTime / timeSlotDuration); // Numero totali timeslot
    int simulationTimeSlotDeadline = 6 * 60 * 60; // Durata totale di un servizio in secondi

    int tsDeadline = ceil(simulationTimeSlotDeadline / timeSlotDuration); // Timeslot entro cui eseguire un servizio

    cout<<"\ntimeSlotTotali:"<<timeSlotTotali;
    cout<<"\ntsDeadline:"<<tsDeadline;

    /*
    std::vector<Request> requests;

    for (int i = 0; i < 10; i++) {
        requests.insert(requests.end(), {i, 0, 1, -1});
    }


    for (int i = 0; i < 10; i++) {
        std::cout<<"\nRequest: " << requests[i].getId();
    }

    /*
    VisibilityMatrix matrix(timeSlotTotali,N,M);
    matrix.setValue(0,0,0,1);
    matrix.initialize();
    matrix.showMatrix();
    */

    return 0;
}
