#include "Agent.h"
// added:
#include "SelectionPolicy.h"
#include "Simulation.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), myCoalitionId(-1), canIsuggest(true)
{
}

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy, int coalitionId) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), myCoalitionId(coalitionId), canIsuggest(true)
{
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}
void Agent::setMyCoalition(int coalition)
{
    myCoalitionId = coalition;
}
int Agent::getMyCoalition() const
{
    return myCoalitionId;
}
void Agent::step(Simulation &sim)
{
    if (canIsuggest)
        mSelectionPolicy->Select(sim,mPartyId,canIsuggest,mAgentId,myCoalitionId);
    // if needed 'canIsuggest' will be updated in stepForAgents
}

Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), myCoalitionId(other.myCoalitionId), canIsuggest(other.canIsuggest)
{ // copy constructor
}

Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), myCoalitionId(other.myCoalitionId), canIsuggest(other.canIsuggest)
{ // move constructor
    other.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(const Agent &other)
{ // copy assingment oprator
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    myCoalitionId = other.myCoalitionId;
    canIsuggest = other.canIsuggest;
    return *this;
}

Agent &Agent::operator=(Agent &&other)
{ // move assingment oprator
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    myCoalitionId = other.myCoalitionId;
    canIsuggest = other.canIsuggest;
    if(this!=&(other)){
    if (mSelectionPolicy)
        delete (mSelectionPolicy);
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    }
    return *this;
}

Agent::~Agent()
{
    delete (mSelectionPolicy);
}

//last added
SelectionPolicy* Agent::cloneSelectionPolicy(){
    return mSelectionPolicy->clone();
}