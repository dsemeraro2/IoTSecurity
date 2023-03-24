#include "Request.h"

Request::Request(int id, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone) : id(id), tsGenerate(tsGenerate),
                                                                                      tsDeadline(tsDeadline), tsDone(tsDone) {
    this->id = id;
    this->tsGenerate = tsGenerate;
    this->tsDeadline = tsDeadline;
    this->tsDone = 0;

}

int Request::getId() const {
    return id;
}

float Request::getTsGenerate() const {
    return tsGenerate;
}

float Request::getTsDeadline() const {
    return tsDeadline;
}

float Request::getTsDone() const {
    return tsDone;
}

void Request::setTsDone(float tsDone) {
    Request::tsDone = tsDone;
}

void Request::generatorRequest(){

}
void Request::addRequest(){

}

void Request::oldRequest(){

}
