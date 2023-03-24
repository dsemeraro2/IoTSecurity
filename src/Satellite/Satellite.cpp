#include "Satellite.h"

Satellite::Satellite(int id, float cpu, float ram, std::vector<Service> services) : id(id), cpu(cpu), ram(ram),
                                                                         services(services) {

    this->id = id;
    this->cpu = cpu;
    this->ram = ram;
    this->services = services;

}

int Satellite::getId() const {
    return id;
}

float Satellite::getCpu() const {
    return cpu;
}

float Satellite::getRam() const {
    return ram;
}

const std::vector<Service> &Satellite::getServices() const {
    return services;
}
