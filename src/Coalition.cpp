#include "Coalition.h"

Coalition::Coalition(int id, int numOfMandats, int partyId) : idCoalition(id), numOfMandats(numOfMandats), parties({partyId})
{
}

int Coalition ::getNumOfMandats()
{
    return numOfMandats;
}
void Coalition ::setNumOfMandats(int toAdd)
{
    numOfMandats = numOfMandats + toAdd;
}

int Coalition ::getIdCoalition()
{
    return idCoalition;
}

void Coalition ::addParty(int partyId)
{
    parties.push_back(partyId);
}

vector<int> Coalition::getParties() const
{
    return parties;
}
