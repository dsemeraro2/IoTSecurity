#include "Satellite.h"

Satellite::Satellite(int id) : id(id) {}

int Satellite::getId() const {
    return id;
}

void Satellite::setId(int id) {
    Satellite::id = id;
}

float Satellite::getCpu() const {
    return cpu;
}

void Satellite::setCpu(float cpu) {
    Satellite::cpu = cpu;
}

float Satellite::getRam() const {
    return ram;
}

void Satellite::setRam(float ram) {
    Satellite::ram = ram;
}

