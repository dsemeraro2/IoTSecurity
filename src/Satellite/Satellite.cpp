#include "Satellite.h"


int Satellite::getId() const {
    return id;
}

Satellite::Satellite(int id, float cpu, float ram, Service **services) : id(id), cpu(cpu), ram(ram),
                                                                         services(services) {

    this->id = id;
    this->cpu = cpu;
    this->ram = ram;
    for (int i = 0; i < MAXSERVICES; i++) {
        this->services[i] = services[i];
    }

}




/*
const Service *Satellite::getServices() const {
    return services;
}
*/