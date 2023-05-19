#include "Request.h"

Request::Request(int idRequest, int idCluster, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone, int idService)
        : idRequest(idRequest), (idCluster), tsGenerate(
        tsGenerate), tsDeadline(tsDeadline), tsDone(tsDone), idService(idService) {}

int Request::getIdRequest() const {
    return idRequest;
}

int Request::getIdCluster() const {
    return idCluster;
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

void Request::setIdRequest(int idRequest) {
    Request::idRequest = idRequest;
}

void Request::setTsDone(int tsDone) {
    Request::tsDone = tsDone;
}

int Request::getIdService() const {
    return idService;
}

void Request::showRequests(std::vector<Request> requests) {
    for (int i = 0; i < 10; i++) {
        std::cout << "\nRequest: " << requests[i].idCluster << " tsGenerate: " << requests[i].tsGenerate
                  << " tsDeadline: " << requests[i].tsDeadline << " tsDone: " << requests[i].tsDone;
    }
}

