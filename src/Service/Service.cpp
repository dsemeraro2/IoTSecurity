#include "Service.h"

Service::Service(int id, const std::string &name, float cpuUsed, float ramUsed) : id(id), name(name), cpuUsed(cpuUsed), ramUsed(ramUsed){}

int Service::getId() const {
    return id;
}

const std::string &Service::getName() const {
    return name;
}

float Service::getCpuUsed() const {
    return cpuUsed;
}

float Service::getRamUsed() const {
    return ramUsed;
}
