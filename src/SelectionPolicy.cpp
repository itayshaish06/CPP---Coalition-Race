#include "SelectionPolicy.h"
#include "Agent.h"
#include "Graph.h"
#include "Simulation.h"

// virtual function
MandatesSelectionPolicy *MandatesSelectionPolicy::clone()
{
    return new MandatesSelectionPolicy();
}

// virtual function
void MandatesSelectionPolicy::Select(Simulation &s, int partyId, bool &canIsuggest, int agentID, int coalitionId)
{
    Graph &graph = s.getGraph2();
    int numOfJointNeighbors = 0; // represents the number of Neighbors in state joint or those who already got suggest from my coalition
    int numOfNeighbors = 0;
    int numOfVertices = graph.getNumVertices();
    int numOfMandates = 0;
    int toSuggest = -1;
    for (int neigborpartyId = 0; neigborpartyId < numOfVertices; neigborpartyId++)
    {
        int edgeWeightTemp = graph.getEdgeWeight(partyId, neigborpartyId);
        if (edgeWeightTemp > 0)
        {
            numOfNeighbors++;
            const Party &tmp = graph.getParty(neigborpartyId);
            if (tmp.getState() == Joined)
                numOfJointNeighbors++;
            else
            {
                // tmp.getState() != Joined
                int tmpMandates = tmp.getMandates();
                if (tmpMandates > numOfMandates)
                {
                    if (tmp.checkSuggestions(coalitionId) == false)
                    {
                        numOfMandates = tmpMandates;
                        toSuggest = neigborpartyId;
                    }
                    else
                    {
                        // tmp.checkSuggestions(coalitionId)  == true
                        numOfJointNeighbors++;
                    }
                }
            }
        }
    }
    if (numOfJointNeighbors == numOfNeighbors) // there is no party to suggest an offer
        canIsuggest = false;
    else
    {
        // we send a suggestion to the party last saved in pointer toSuggest
        graph.getParty2(toSuggest).addSuggest(coalitionId, agentID);
    }
}

// virtual function
EdgeWeightSelectionPolicy *EdgeWeightSelectionPolicy::clone()
{
    return new EdgeWeightSelectionPolicy();
}

// virtual function
void EdgeWeightSelectionPolicy::Select(Simulation &s, int partyId, bool &canIsuggest, int agentID, int coalitionId)
{
    Graph &graph = s.getGraph2();
    int numOfJointNeighbors = 0; // represents the number of Neighbors in state joint or those who already got suggest from my coalition
    int numOfNeighbors = 0;
    int numOfVertices = graph.getNumVertices();
    int toSuggest = -1;
    int biggestEdgeWeight = 0;
    for (int neigborpartyId = 0; neigborpartyId < numOfVertices; neigborpartyId++)
    {
        int edgeWeightTemp = graph.getEdgeWeight(partyId, neigborpartyId);
        if (edgeWeightTemp > 0)
        {
            numOfNeighbors++;
            const Party &tmp = graph.getParty(neigborpartyId);
            if (tmp.getState() == Joined)
                numOfJointNeighbors++;
            else
            {
                // tmp.getState() != Joined
                if (edgeWeightTemp > biggestEdgeWeight)
                {
                    if (tmp.checkSuggestions(coalitionId) == false)
                    {
                        biggestEdgeWeight = edgeWeightTemp;
                        toSuggest = neigborpartyId;
                    }
                    else
                    {
                        // tmp.checkSuggestions(coalitionId)  == true
                        numOfJointNeighbors++;
                    }
                }
            }
        }
    }
    if (numOfJointNeighbors == numOfNeighbors) // there is no party to suggest an offer
        canIsuggest = false;
    else
    {
        // we send a suggestion to the party last saved in pointer toSuggest
        graph.getParty2(toSuggest).addSuggest(coalitionId, agentID);
    }
}