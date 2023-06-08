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
    std::vector<Solution> tabuList;

    TabuSearch(int timeSlot, int satellites, std::vector<Service> services, const std::vector<Request> &requests,
               const Solution &solution, const VisibilityMatrix &visibilityMatrix, const AllocationServicesMatrix &allocationServicesMatrix);

    void optimizationTabuSearch(int timeSlotInitial, int timeSlotTotali);

    Solution swapMove(Solution &tempSolution, int sourceTimeSlot, int sourceService, int sourceSatellite,
                      int destTimeSlot, int destService, int destSatellite);

    bool stopCondition(std::vector<float> historySolution);

    Solution tabuSearchIterate(std::vector<Request> tempRequests, int currentIndex);

    bool isSolutionInTabuList(Solution &sourceSol);

    bool compareSolution(const Solution &sourceSol, const Solution &destSol);

    void filterTsDone(std::vector<Request> &requests, std::vector<Service> services, Solution *solution,
                                   VisibilityMatrix visibilityMatrix, bool editMode, int currentTimeSlot);

    bool compareBestSolution(const Solution& sourceSol, const Solution& destSol);
};


#endif //IOTSECURITY_TABUSEARCH_H
