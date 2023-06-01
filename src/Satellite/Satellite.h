#ifndef IOTSECURITY_SATELLITE_H
#define IOTSECURITY_SATELLITE_H


#include <vector>
#include "../Service/Service.h"

/*
 * Modello di satelliti: PowerEdge R6515 con AMD EPYC 7702p, 2 GHz
 * CPU: 2 000 000 * 64 numero di CPU (64)
 * RAM: 64 GB di ram
*/

class Satellite {

private:
    int id;
    float cpu;
    float ram;
    float cpuUsed;
    float ramUsed;
    std::vector<Service> services;

public:
    Satellite(int id, float cpu, float ram);

    int getId() const;

    float getCpu() const;

    float getRam() const;

    float getCpuUsed() const;

    float getRamUsed() const;

    void setCpuUsed(float cpuUsed);

    void setRamUsed(float ramUsed);

    const std::vector<Service> &getServices() const;

    bool addService(Service service);

    void removeService(int indexService);

    bool checkService(int indexService);

    int numberOfServices();
};


#endif //IOTSECURITY_SATELLITE_H
