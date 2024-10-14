#include "Simulation.h"
// added:
#include "SelectionPolicy.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), myCoalition({}), maxCoalition(0), numOfJoinedParties(0), totalNumOfParties(graph.getNumVertices())
{
    int i = 0;
    for (Agent &agent : mAgents)
    {
        int partyId = agent.getPartyId();
        int mandates = graph.getParty(partyId).getMandates();
        myCoalition.push_back((Coalition(i, mandates, partyId)));
        agent.setMyCoalition(i);
        if (mandates > maxCoalition)
            maxCoalition = mandates;
        i++;
    }
    // at the end of the for loop 'i' represnts the number of numOfJoinedParties
    numOfJoinedParties = i;
}

void Simulation::step()
{
    mGraph.stepForParties(*this);
    for (Agent &agent : mAgents)
    {
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    if (maxCoalition >= 61 || numOfJoinedParties == totalNumOfParties)
        return true;
    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraph2()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

const int Simulation ::getMaxCoalition() const
{
    return maxCoalition;
}

void Simulation ::setMaxCoalition(int numOfMandats)
{
    maxCoalition = numOfMandats;
}

const int Simulation ::getNumOfJoinedParties() const
{
    return numOfJoinedParties;
}

void Simulation ::addJoinedParties()
{
    numOfJoinedParties++;
}

Coalition &Simulation::getCoalition(int index)
{
    return myCoalition[index];
}

void Simulation::Join(int coalitionId, int numOfMandates, int partyId, int formerAgent)
{
    myCoalition[coalitionId].setNumOfMandats(numOfMandates);
    myCoalition[coalitionId].addParty(partyId);
    int mandates = myCoalition[coalitionId].getNumOfMandats();
    if (mandates > maxCoalition)
    {
        maxCoalition = mandates;
    }
    numOfJoinedParties++;
    //from int agent id - get Agent - get mSelectionPolicy - call clone()
    /*SelectionPolicy *sp;
    if (policyOfSelect)
        sp = new EdgeWeightSelectionPolicy;
    else
        sp = new MandatesSelectionPolicy;*/
    int clonedAgentId = mAgents.size();
    mAgents.push_back(Agent(clonedAgentId, partyId, mAgents[formerAgent].cloneSelectionPolicy(), coalitionId));
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> partiesByCoalitions;
    int size = myCoalition.size();
    for (int i = 0; i < size; i++)
    {
        partiesByCoalitions.push_back(myCoalition[i].getParties());
    }
    return partiesByCoalitions;
}
