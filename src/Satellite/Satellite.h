#ifndef IOTSECURITY_SATELLITE_H
#define IOTSECURITY_SATELLITE_H


#include <vector>
#include "../Service/Service.h"

class Satellite {

private:
    int id;
    float cpu;
    float ram;
    std::vector<Service> services;

public:
    Satellite(int id, float cpu, float ram, std::vector<Service> services);

    int getId() const;

    float getCpu() const;

    float getRam() const;

    const std::vector<Service> &getServices() const;

};


#endif //IOTSECURITY_SATELLITE_H
