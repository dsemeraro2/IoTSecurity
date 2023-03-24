#ifndef IOTSECURITY_REQUEST_H
#define IOTSECURITY_REQUEST_H

#define timeSlot float

class Request {

    int id;
    timeSlot tsGenerate;
    timeSlot tsDeadline;
    timeSlot tsDone;

public:
    Request(int id, timeSlot tsGenerate, timeSlot tsDeadline, timeSlot tsDone);

    void setTsDone(float tsDone);

    int getId() const;

    float getTsGenerate() const;

    float getTsDeadline() const;

    float getTsDone() const;

    void generatorRequest();

    void addRequest();

    void oldRequest();
};


#endif //IOTSECURITY_REQUEST_H
