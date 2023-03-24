#ifndef IOTSECURITY_SERVICE_H
#define IOTSECURITY_SERVICE_H


#include <string>

class Service {

private:
    int id;
    std::string name;
    float cpuUsed;
    float ramUsed;

public:

    Service(int id, const std::string &name, float cpuUsed, float ramUsed);

    int getId() const;

    const std::string &getName() const;

    float getCpuUsed() const;

    float getRamUsed() const;
};


#endif //IOTSECURITY_SERVICE_H
