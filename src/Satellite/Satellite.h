#ifndef IOTSECURITY_SATELLITE_H
#define IOTSECURITY_SATELLITE_H


class Satellite {

private:
    int id;
    float cpu;
    float ram;
    //Service services[];

public:
    explicit Satellite(int id); //Constructor

    int getId() const;

    void setId(int id);

    float getCpu() const;

    void setCpu(float cpu);

    float getRam() const;

    void setRam(float ram);
};


#endif //IOTSECURITY_SATELLITE_H
