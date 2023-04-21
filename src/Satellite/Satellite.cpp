#include "Satellite.h"

Satellite::Satellite(int id, float cpu, float ram) {
    this->id = id;
    this->cpu = cpu;
    this->ram = ram;
    this->cpuUsed = cpu;
    this->ramUsed = ram;
    //this->services;
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

float Satellite::getCpuUsed() const {
    return cpuUsed;
}

float Satellite::getRamUsed() const {
    return ramUsed;
}

void Satellite::setCpuUsed(float cpuUsed) {
    Satellite::cpuUsed = cpuUsed;
}

void Satellite::setRamUsed(float ramUsed) {
    Satellite::ramUsed = ramUsed;
}

const std::vector<Service> &Satellite::getServices() const {
    return services;
}

bool Satellite::addService(Service service){

    float cpuRimanente = this->getCpuUsed()-service.getCpuUsed();
    float ramRimanente = this->getRamUsed()-service.getRamUsed();

    if(cpuRimanente >= 0 && ramRimanente >= 0){
        setCpuUsed(cpuRimanente);
        setRamUsed(ramRimanente);
        this->services.push_back(service);
        return 1; //True
    } else {
        return 0; //False
    }

}

void Satellite::removeService(int indexService){

    this->setCpuUsed(this->getCpuUsed()+this->services[indexService].getCpuUsed());
    this->setRamUsed(this->getRamUsed()+this->services[indexService].getRamUsed());

    this->services.erase(this->services.begin()+indexService);

}

bool Satellite::checkService(int idService){

    for(int i=0; i<this->services.size(); i++){
        if(this->services[i].getId() == idService)
            return true;
    }

    return false;
}

