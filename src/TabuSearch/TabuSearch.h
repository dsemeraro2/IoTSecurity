#ifndef IOTSECURITY_TABUSEARCH_H
#define IOTSECURITY_TABUSEARCH_H

#include "../Solution/Solution.h"
#include "../Request/Request.h"
#include "../VisibilityMatrix/VisibilityMatrix.h"
#include "../AllocationServicesMatrix/AllocationServicesMatrix.h"

class TabuSearch {
public:
    int timeSlot;
    int satellites;
    std::vector<Service> services;
    std::vector<Request> requests;
    Solution solution;
    VisibilityMatrix visibilityMatrix;
    AllocationServicesMatrix allocationServicesMatrix;

    TabuSearch(int timeSlot, int satellites, std::vector<Service> services, const std::vector<Request> &requests,
               const Solution &solution, const VisibilityMatrix &visibilityMatrix, const AllocationServicesMatrix &allocationServicesMatrix);

    void optimizationTabuSearch(int timeSlotInitial, int timeSlotTotali);

    void swapMove(Solution tempSolution, int sourceTimeSlot, int service, int sourceSatellite,
                  int destTimeSlot, int destSatellite);

    bool stopCondition(std::vector<float> historySolution);

    Solution tabuSearchIterate(std::vector<Request> tempRequests);
};


#endif //IOTSECURITY_TABUSEARCH_H
