#include "AllocationServicesMatrix.h"
#include "../Simulation/Simulation.h"

AllocationServicesMatrix::AllocationServicesMatrix(int t, int n, int m) {
    this->tMax = t; //TimeSlote
    this->nMax = n; //Servizi
    this->mMax = m; //satelliti
    // Allocazione dinamica della matrice tramite il metodo new
    data = new int **[t];
    for (int i = 0; i < t; i++) {
        data[i] = new int *[n];
        for (int j = 0; j < n; j++) {
            data[i][j] = new int[m];
            for (int k = 0; k < m; k++) {
                data[i][j][k] = 0;
            }
        }
    }
}

int AllocationServicesMatrix::getNMax() const {
    return nMax;
}

int AllocationServicesMatrix::getMMax() const {
    return mMax;
}

int AllocationServicesMatrix::getTMax() const {
    return tMax;
}

// Set a value a un'elemento della matrice alle coordinate (tMax,nMax,mMax)
void AllocationServicesMatrix::setValue(int t, int n, int m, int value) {
    // Controlla se gli indici sono validi
    if (t < 0 || t >= tMax || n < 0 || n >= nMax || m < 0 || m >= mMax) {
        throw std::out_of_range("Indici fuori dal range");
    }
    // Assegna il valore alla posizione specificata
    data[t][n][m] = value;
}

void AllocationServicesMatrix::showMatrix() {

}

void AllocationServicesMatrix::initialize(Solution *solution, std::vector<Service> services) {

    int sizeOfServices = services.size();

    for (int t = 0; t < tMax; t++) {
        //for (int m = 0; m < mMax; m++) {
        for (int n = 0; n < nMax; n++) {
            int m = (n + t) % mMax;
            data[t][n][m] = 1;
            solution->constellations[t].satellaties[m].addService(
                    getServiceById(initializeServices(), n % sizeOfServices));
        }
        //}
    }

}
