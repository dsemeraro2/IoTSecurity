#ifndef IOTSECURITY_SERVICE_H
#define IOTSECURITY_SERVICE_H

#include <string>


/*
 * Servizi:
 * Fortigate: 34.8 cyclesForBit, 3 servicesForBundle, [2-4] GB Ram, 92000 NarrowBandIoT bit for second
 * Cisco: 11.1 cyclesForBit, 2 servicesForBundle, [2-4] GB Ram, 92000 NarrowBandIoT bit for second
 * Junioper: 6.2 cyclesForBit, 3 servicesForBundle, [2-4] GB Ram, 92000 NarrowBandIoT bit for second
 * Other: 40.5 cyclesForBit, 2 servicesForBundle, [2-4] GB Ram, 92000 NarrowBandIoT bit for second
 */
class Service {

private:
    int id;
    //std::string name;
    float cpuUsed;
    float ramUsed;

public:

    //Service(int id, const std::string &name, float cpuUsed, float ramUsed);
    Service(int id, float cpuUsed, float ramUsed);

    int getId() const;

    const std::string &getName() const;

    float getCpuUsed() const;

    float getRamUsed() const;

};


#endif //IOTSECURITY_SERVICE_H
