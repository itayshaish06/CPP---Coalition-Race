#pragma once
//added:
#include <vector>
using std::vector;

class Coalition
{
public:
    Coalition(int idAgent,int numOfMandats, int partyId);

    int getNumOfMandats();
    void setNumOfMandats(int toAdd);
    int getIdCoalition();
    void addParty(int partyId);
    vector<int> getParties() const;

private:
    int idCoalition;
    int numOfMandats;
    vector<int> parties;
};
