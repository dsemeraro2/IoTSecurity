#include "Request.h"
#include "../Simulation/Simulation.h"

Request::Request(int id, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone, int idService) : id(id), tsGenerate(
        tsGenerate),
                                                                                                     tsDeadline(
                                                                                                             tsDeadline),
                                                                                                     tsDone(tsDone),
                                                                                                     idService(
                                                                                                             idService) {


}

int Request::getId() const {
    return id;
}

timeSlot Request::getTsGenerate() const {
    return tsGenerate;
}

timeSlot Request::getTsDeadline() const {
    return tsDeadline;
}

timeSlot Request::getTsDone() const {
    return tsDone;
}

void Request::setTsDone(float tsDone) {
    Request::tsDone = tsDone;
}

int Request::getIdService() const {
    return idService;
}

void Request::showRequests(std::vector<Request> requests) {
    for (int i = 0; i < 10; i++) {
        std::cout << "\nRequest: " << requests[i].id << " tsGenerate: " << requests[i].tsGenerate
                  << " tsDeadline: " << requests[i].tsDeadline << " tsDone: " << requests[i].tsDone;
    }
}

