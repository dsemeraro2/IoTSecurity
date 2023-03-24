#include "Satellite.h"


int Satellite::getId() const {
    return id;
}

Satellite::Satellite(int id, float cpu, float ram) : id(id), cpu(cpu), ram(ram) {
    this->id = id;
    this->cpu = cpu;
    this->ram = ram;
}
/*
const Service *Satellite::getServices() const {
    return services;
}
*/