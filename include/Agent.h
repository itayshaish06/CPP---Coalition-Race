#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy, int coalitionId);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setMyCoalition(int coalition);
    int getMyCoalition() const;
    //Rule of 5:
    Agent(const Agent &other); //copy constructor
    Agent(Agent &&other); //move constructor
    Agent& operator=(const Agent& other);//copy assingment oprator
    Agent& operator=(Agent&& other);//move assingment oprator
    virtual ~Agent();

    //last added
    SelectionPolicy* cloneSelectionPolicy();




private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int myCoalitionId;
    bool canIsuggest;
};
