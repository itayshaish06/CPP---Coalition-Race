#include "JoinPolicy.h"
#include "Simulation.h"
#include "Party.h"

// virtual function
LastOfferJoinPolicy* LastOfferJoinPolicy::clone(){
    return new LastOfferJoinPolicy();
}

// virtual function
void LastOfferJoinPolicy::Join(Simulation &s, Party &p, int partyId){
    vector<int> &suggestions = p.getSuggestionVector();
    vector<int> &agentsID = p.getagentsIDVector();
    int coalitionid = suggestions.back();
    int formerAgentId = agentsID.back();
    int mandates = p.getMandates();
    s.Join(coalitionid, mandates, partyId, formerAgentId);
}

// virtual function
MandatesJoinPolicy* MandatesJoinPolicy::clone(){
    return new MandatesJoinPolicy();
}

// virtual function
void MandatesJoinPolicy::Join(Simulation &s, Party &p, int partyId){
    vector<int> &suggestions = p.getSuggestionVector();
    vector<int> &agentsID = p.getagentsIDVector();
    int coalitionid = -1;
    int formerAgentId = -1;
    int maxMandates = 0;
    int suggestions_size = suggestions.size();
    for (int i = 0; i < suggestions_size; i++)
    {
    int tempMandates = s.getCoalition(suggestions[i]).getNumOfMandats();
    if (tempMandates > maxMandates)
        {
            maxMandates = tempMandates;
            coalitionid = suggestions[i];
            formerAgentId = agentsID[i];
        }
    }
    s.Join(coalitionid, maxMandates, partyId, formerAgentId);
}
