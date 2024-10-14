#pragma once
#include <string>

using std::string;

class JoinPolicy;
class Simulation;

//added:
#include <vector>
using std::vector;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    void addSuggest(int numOfCoalition, int agentId);
    bool checkSuggestions(int numOfCoalition) const;
    vector<int>& getSuggestionVector();
    vector<int>& getagentsIDVector();

    //Rule of 5:
    Party(const Party &other); //copy constructor
    Party(Party &&other); //move constructor
    Party& operator=(const Party& other);//copy assingment oprator
    Party& operator=(Party&& other);//move assingment oprator
    virtual ~Party();

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    vector<int> suggestions;
    vector<int> agentsID;
};
