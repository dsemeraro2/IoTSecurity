#include "Simulation.h"
#include "../VisibilityMatrix/VisibilityMatrix.h"

int secondsAtDay = 84600; // Secondi in un giorno
int simulationTime = 24 * 60 * 60; // Durata totale della simulazione in secondi
int durataRivoluzione = 94 * 60; // Durata rivoluzione di 1 satellite in secondi
float timeSlotDuration = durataRivoluzione / M; // Intervallo durata visibilità di M satelliti in secondi
int timeSlotTotali = ceil(simulationTime / timeSlotDuration); // Numero totali timeslot
int simulationDeadline = 6 * 60 * 60; // Durata totale di un servizio in secondi
int timeSlotDeadline = ceil(simulationDeadline / timeSlotDuration); // Timeslot entro cui eseguire un servizio

//n*m*tMax dove n = numero cluster, m = numero leo satellite, t = durata totale simulazione
int T = timeSlotTotali;
int N = 10;
int M = 3;

std::vector<Cluster> initializeClusters() {
    std::vector<Cluster> clusters;
    for (int i = 0; i < N; i++) {
        clusters.push_back({i});
    }
    return clusters;
};

std::vector<Service> initializeServices() {

    //List of services defined in the class
    std::vector<double> listOfCycleForBit = {34.8, 11.1, 6.2, 40.5};
    std::vector<int> listServicesForBundle = {3, 2, 3, 2};
    std::vector<int> listRam = {2, 4};
    int NarrowBandIoTBps = 92000;

    std::vector<Service> services;

    for (int i = 0; i < N; i++) {
        int index = rand() % listOfCycleForBit.size();
        float ramUsed = 0;

        for (int j = 0; j < listServicesForBundle[index]; j++) {
            int indexRam = rand() % listRam.size();
            ramUsed = ramUsed + listRam[indexRam];
        }

        Service service = Service(i, listOfCycleForBit[index] * NarrowBandIoTBps, ramUsed);
        services.push_back(service);
    }
    return services;
};


std::vector<Request> initializeRequests(std::vector<Service> services, int seedRand, float lambda) {

    srand(seedRand);

    std::vector<Request> requests;

    int countIdRequest = 0;

    int sizeService = services.size();

    for (int i = 0; i < N; i++) {

        int t_next = 0; // Istante in cui avviene l'evento, tempo globale che scorre
        int next_time = 0; // E' la differenza di tempo che serve per scorrere il tempo globale

        while (t_next < (timeSlotTotali - timeSlotDeadline)) {
            // Poisson
            float r = ((float) rand() / (RAND_MAX));
            float float_next_time = -(log(1.0 - r) / lambda);

            next_time = ceil(float_next_time);

            t_next = t_next + next_time;

            if (t_next <= (timeSlotTotali - timeSlotDeadline)) {
                requests.push_back({countIdRequest++, i, t_next, t_next + timeSlotDeadline, -1, i % sizeService});
            }
        }
    }
    return requests;
}


Service getServiceById(std::vector<Service> listOfServices, int id) {
    Service tempServizio = Service(-1, 0, 0);
    for (int i = 0; i < listOfServices.size(); i++) {
        if (listOfServices[i].getId() == id)
            tempServizio = listOfServices[id];
    }
    return tempServizio;
}

int objectiveFunction(std::vector<Request> requests, std::vector<Service> services, Solution *solution,
                      VisibilityMatrix visibilityMatrix, bool editMode) {

    std::cout << "Request size: " << requests.size() << "\n";
    int f = 0; //Ritardo da minimizzare
    bool serviceDeployed = false;

    //i numero delle richieste
    for (int i = 0; i < requests.size(); i++) {

        serviceDeployed = false;
        //std::cout << "i:" << i << "\n";

        Service tempService = getServiceById(services, requests[i].getIdService());

        int delayRequestCollection = 1; //Delay della raccolta del servizio verso i satelliti, 1 timeslot
        int delayRequestOptimization = 2; //Delay della ottimizzazione + deploy del servizio, 2 timeslot (contenente l'elaborazione + il deploy)

        int initialTimeSlot = requests[i].getTsGenerate();
        int deadlineTimeSlot = requests[i].getTsDeadline();

        if (tempService.getId() != -1) {

            //j numero della deadlineTimeSlot del singolo servizio DOVREBBE ESSERE IL MASSIMO
            for (int j = initialTimeSlot + delayRequestCollection + delayRequestOptimization;
                 j < deadlineTimeSlot; j++) {

                //k numero dei satelliti
                for (int k = 0; k < solution->constellations[j].satellaties.size(); k++) {

                    std::vector<Service> listServicesSatellite = solution->constellations[j].satellaties[k].getServices();

                    //std::cout << "Richiesta i: " << i << " Timeslot j: " << j << "Satellite k: " << k << "\n";
                    //m Numero dei diversi servizi del satellite
                    for (int m = 0; m < listServicesSatellite.size(); m++) {

                        if (listServicesSatellite[m].getId() == tempService.getId()) {
                            if (visibilityMatrix.getValue(j, tempService.getId(), k) == 1) {
                                serviceDeployed = true;
                                f = f + (j - initialTimeSlot);
                                //std::cout << "Funzione obiettivo: " << f << "\n";
                                break;
                            }
                        }
                    }
                    if (serviceDeployed) break;
                }
                if (serviceDeployed) break;
            }

            if (editMode && !serviceDeployed) {
                //Codice di aggiunta servizi sul satelliti

                //for (int j = initialTimeSlot + delayRequestCollection + delayRequestOptimization;
                //     j < deadlineTimeSlot; j++) {

                for (int j = deadlineTimeSlot;
                     j > initialTimeSlot + delayRequestCollection + delayRequestOptimization; j--) {
                    //k numero dei satelliti
                    for (int k = 0; k < solution->constellations[j].satellaties.size(); k++) {

                        if (visibilityMatrix.getValue(j, tempService.getId(), k) == 1) {

                            bool allocated = solution->constellations[j].satellaties[k].addService(tempService);

                            if (allocated) {
                                serviceDeployed = true;
                                f = f + (j - initialTimeSlot);
                                std::cout << "Funzione obiettivo: " << f << "\n";
                            }
                            break;
                        }
                        if (serviceDeployed) break;
                    }
                    if (serviceDeployed) break;
                }
                if (!serviceDeployed) {
                    //Se non è in modalità modifica edit mode falso e il servizio non è stato deployato ritorna infinito
                    return INT_MAX;
                }

            } else if (!editMode && !serviceDeployed) {
                //Se non è in modalità modifica edit mode falso e il servizio non è stato deployato ritorna infinito
                return INT_MAX;
            }

        } else {
            std::cout << "Errore Servizio non trovato! " << requests[i].getIdCluster() << "\n";
            objectiveFunction(requests, services, solution, visibilityMatrix, false);
        }
    }

    return f;
}

// 3 Funzioni importanti per la TabuSearch:
// Funzione obiettivo: Definita
// Tabu List Management: Lista delle soluzioni gia visitati
// Generate Neighbords: La funzione swap(?) ovvero generare nuovi vicini da valutare

// Funzione per salvare sul file le costellazioni
void saveSolutionToFile(const Solution &solution, const std::string &folderPath, const std::string &fileName,
                        int constellationIndex) {
    std::filesystem::create_directory(folderPath);

    std::string filename = folderPath + fileName + std::to_string(constellationIndex) + ".txt";
    std::ofstream file(filename);

    if (file.is_open()) {
        // Salva le informazioni generali della soluzione
        //file << "Time Slot: " << solution.timeSlot << "\n";
        file << "f: " << solution.f << "\n";
        file << "Constellations: " << solution.constellations.size() << "\n\n";

        // Salva le informazioni di ogni costellazione
        for (const Constellation &constellation: solution.constellations) {
            //file << "Constellation (mMax = " << constellation.mMax << ")\n";
            file << "Satellites: " << constellation.satellaties.size() << "\n";

            // Salva le informazioni di ogni satellite nella costellazione
            for (const Satellite &satellite: constellation.satellaties) {
                file << "Satellite (id = " << satellite.getId() << ", cpu = " << satellite.getCpu()
                     << ", ram = " << satellite.getRam() << ")\n";
                file << "Services: " << satellite.getServices().size();

                // Salva le informazioni di ogni servizio nel satellite
                for (const Service &service: satellite.getServices()) {
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


