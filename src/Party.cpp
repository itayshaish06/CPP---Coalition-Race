#include "Party.h"
// added:
#include "JoinPolicy.h"
#include "Simulation.h"
#include "Coalition.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(0), suggestions({}), agentsID({})
{
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string &Party::getName() const
{
    return mName;
}

void Party::addSuggest(int numOfCoalition, int agentId)
{
    suggestions.push_back(numOfCoalition);
    agentsID.push_back(agentId);
    if (mState == Waiting)
        mState = CollectingOffers;
}

bool Party::checkSuggestions(int numOfCoalition) const
{
    int suggestions_size = suggestions.size();
    for (int i = 0; i < suggestions_size; i++)
        if (suggestions[i] == numOfCoalition)
            return true;
    return false;
}

vector<int>& Party::getSuggestionVector(){
    return suggestions;
}

vector<int>& Party::getagentsIDVector(){
    return agentsID;
}

void Party::step(Simulation &s)
{
    if (mState == CollectingOffers)
    {
        timer++;
        if (timer == 3)
        {
            mJoinPolicy->Join(s,*this,mId);
            mState = Joined;
        }
    }
}

// Rule of 5:

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), timer(other.timer), suggestions({}), agentsID({})
{ // copy constructor
    int tempSize = other.suggestions.size();
    for (int i = 0; i < tempSize; i++)
    {
        suggestions.push_back(other.suggestions[i]);
    }
    tempSize = other.agentsID.size();

    for (int i = 0; i < tempSize; i++)
    {
        agentsID.push_back(other.agentsID[i]);
    }
}

Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), timer(other.timer), suggestions({}), agentsID({})
{
    // move constructor
    int tempSize = other.suggestions.size();
    for (int i = 0; i < tempSize; i++)
    {
        suggestions.push_back(other.suggestions[i]);
    }
    tempSize = other.agentsID.size();

    for (int i = 0; i < tempSize; i++)
    {
        agentsID.push_back(other.agentsID[i]);
    }
    other.mJoinPolicy = nullptr;
}

Party &Party::operator=(const Party &other)
{
    // copy assingment oprator
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    timer = other.timer;
    int tempSize = other.suggestions.size();
    for (int i = 0; i < tempSize; i++)
    {
        suggestions.push_back(other.suggestions[i]);
    }
    tempSize = other.agentsID.size();

    for (int i = 0; i < tempSize; i++)
    {
        agentsID.push_back(other.agentsID[i]);
    }
    if (mJoinPolicy)
        delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy->clone();
    return *this;
}

Party &Party::operator=(Party &&other)
{
    // move assingment oprator
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    timer = other.timer;
    int tempSize = other.suggestions.size();
    for (int i = 0; i < tempSize; i++)
    {
        suggestions.push_back(other.suggestions[i]);
    }
    tempSize = other.agentsID.size();

    for (int i = 0; i < tempSize; i++)
    {
        agentsID.push_back(other.agentsID[i]);
    }
    if(this!=(&other)){
    if (mJoinPolicy)
        delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
    }
    return *this;
}

Party::~Party()
// destructor
{
    delete (mJoinPolicy);
}
