#ifndef IOTSECURITY_SATELLITE_H
#define IOTSECURITY_SATELLITE_H


#include "../Service/Service.h"
#define MAXSERVICES 3

class Satellite {

private:
    int id;
    float cpu;
    float ram;
    Service *services[MAXSERVICES];

public:
    Satellite(int id, float cpu, float ram, Service **services);

    int getId() const;

    float getCpu() const;

    float getRam() const;

    const Service *getServices() const;

};


#endif //IOTSECURITY_SATELLITE_H
