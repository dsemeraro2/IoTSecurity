using namespace std;

#include <iostream>
#include <cmath>
#include <fstream>
#include <filesystem>
#include "VisibilityMatrix/VisibilityMatrix.h"
#include "Request/Request.h"
#include "Simulation/Simulation.h"
#include "Cluster/Cluster.h"
#include "AllocationServicesMatrix/AllocationServicesMatrix.h"
#include "TabuSearch/TabuSearch.h"

Solution generateSolution() {
    return Solution(timeSlotTotali);
}
void saveSolutionToFile (const Solution &solution, const std::string &folderPath, const std::string &fileName, int constellationIndex) {
    std::filesystem::create_directory(folderPath);

    std::string filename = folderPath + fileName + std::to_string(constellationIndex) + ".txt";
    std::ofstream file(filename);

    if (file.is_open()) {
        // Salva le informazioni generali della soluzione
        //file << "Time Slot: " << solution.timeSlot << "\n";
        file << "f: " << solution.f << "\n";
        file << "Constellations: " << solution.constellations.size() << "\n\n";

        // Salva le informazioni di ogni costellazione
        for (const Constellation& constellation : solution.constellations) {
            //file << "Constellation (mMax = " << constellation.mMax << ")\n";
            file << "Satellites: " << constellation.satellaties.size() << "\n";

            // Salva le informazioni di ogni satellite nella costellazione
            for (const Satellite& satellite : constellation.satellaties) {
                file << "Satellite (id = " << satellite.getId() << ", cpu = " << satellite.getCpu()
                     << ", ram = " << satellite.getRam() << ")\n";
                file << "Services: " << satellite.getServices().size();

                // Salva le informazioni di ogni servizio nel satellite
                for (const Service& service : satellite.getServices()) {
                    file << "Service (id = " << service.getId() << ", cpuUsed = " << service.getCpuUsed()
                         << ", ramUsed = " << service.getRamUsed() << ")\n";
                }

                file << "\n";
            }

            file << "\n";
        }

        file.close();
        //std::cout << "Soluzione salvata correttamente su file: " << filename << "\n";
    } else {
        std::cout << "Impossibile aprire il file: " << filename << "\n";
    }
}

int main() {

    //TODO: Da fare una simulazione ad ampio spretto sui cluster, satelliti, eventi e seed
    //n*m*tMax dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
    //int N = 8;
    //int M = 5;

    int numberEventAtDay = 6;

    int seedRand = 2;
    int slotAtDay = ceil(secondsAtDay / timeSlotDuration);
    float lambda = (numberEventAtDay / float(slotAtDay));

    std::vector<Cluster> clusters = initializeClusters();

    std::vector<Service> services = initializeServices();

    Solution solution = generateSolution();

    std::vector<Request> requests = initializeRequests(services, seedRand, lambda);

    AllocationServicesMatrix allocationServicesMatrix{T, N, M};

    //allocationServicesMatrix.initialize(&solution, services);

    VisibilityMatrix visibilityMatrix = VisibilityMatrix(T, N, M);
    visibilityMatrix.initialize();

    //std::cout << "Funzione obiettivo: " << solution.f << "\n";

    //Salvataggio su file prima dell'ottimizzazione
    for (int i = 0; i < solution.constellations.size(); ++i) {
        const Constellation& constellation = solution.constellations[i];
        saveSolutionToFile(solution, "./solution_constellation_old", "/solution_constellation_old_", i);
    }

    // Algoritmo di ottimizzazione
    std::cout << "Ottimizzazione:\n";
    TabuSearch tabuSearch = TabuSearch(T, M, services, requests, solution, visibilityMatrix, allocationServicesMatrix);
    tabuSearch.optimizationTabuSearch(0, T);

    //Salvataggio su file fopo l'ottimizzazione
    for (int i = 0; i < solution.constellations.size(); ++i) {
        const Constellation& constellation = solution.constellations[i];
        saveSolutionToFile(solution, "./solution_constellation_new", "/solution_constellation_new_", i);
    }

    return 0;
}
