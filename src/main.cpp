using namespace std;
#include <iostream>
#include <cmath>
#include "VisibilityMatrix/VisibilityMatrix.h"

//n*m*tMax dove n = numero cluster, m = numero leo satellite, tMax = durata totale simulazione
#define N 8
#define M 5
#define T 5

int main()
{
    int simulation = 24*60*60; //Durata totale della simulazione
    int durataRivoluzione = 94*60; //Durata rivoluzione di 1 satellite
    float timeSlotDuration = durataRivoluzione/M; //Intervallo durata visibilità di M satelliti
    int timeSlotTotali = ceil(simulation/timeSlotDuration);


    cout << "Prova matrice tridimensionale\n";
    VisibilityMatrix matrix(timeSlotTotali,N,M);

    //matrix.setValue(0,0,0,1);

    matrix.initialize();

    matrix.showMatrix();

    return 0;
}
