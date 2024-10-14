#pragma once
//we added:
class Simulation;
class Party;

class JoinPolicy {
    public:
        virtual ~JoinPolicy() = default;
        virtual void Join(Simulation &s, Party &p, int partyId)=0;
        virtual JoinPolicy* clone()=0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        void Join(Simulation &s, Party &p, int partyId);//virtual function
        MandatesJoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        void Join(Simulation &s, Party &p, int partyId);//virtual function
        LastOfferJoinPolicy* clone();
};