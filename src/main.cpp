using namespace std;
#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"

//n*m*t dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
#define N 5
#define M 6
#define T 5

int main()
{
    int simulation = 24*60*60; //Durata totale della simulazione
    int durataRivoluzione = 94*60; //Durata rivoluzione di 1 satellite
    float timeSlotDuration = durataRivoluzione/M; //Intervallo durata visibilità di M satelliti
    int timeSlotTotali = ceil(simulation/timeSlotDuration);

    cout << "Prova matrice tridimensionale\n";
    VisibilityMatrix matrix(N,M,timeSlotTotali);

    matrix.showMatrix();

    return 0;
}
