#pragma once
//we added:
class Agent;
class Simulation;

class SelectionPolicy { 
    public:
        virtual ~SelectionPolicy() = default;
        virtual void Select(Simulation &s, int partyId, bool &canIsuggest, int agentID, int coalitionId)=0;
        virtual SelectionPolicy* clone()=0;

};

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
        void Select(Simulation &s, int partyId, bool &canIsuggest, int agentID, int coalitionId);
        MandatesSelectionPolicy* clone();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
        void Select(Simulation &s, int partyId, bool &canIsuggest, int agentID, int coalitionId);
        EdgeWeightSelectionPolicy* clone();
};