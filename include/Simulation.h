#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;
//added:
#include "Coalition.h"

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    Graph &getGraph2();
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    const int getMaxCoalition() const;
    void setMaxCoalition(int numOfMandats);
    const int getNumOfJoinedParties() const;
    void addJoinedParties();
    Coalition& getCoalition(int index);
    void Join(int coalitionId, int numOfMandates, int partyId, int formerAgent);
    

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> myCoalition; 
    int maxCoalition; //represents the num of mandates of the largest coalition
    int numOfJoinedParties;
    int totalNumOfParties;
};
