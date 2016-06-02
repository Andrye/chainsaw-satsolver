#ifndef _FEEDER_H
#define _FEEDER_H

#include <algorithm>
#include <numeric>
#include <vector>

#include "solver.h"

template <typename ComputationContext>
class simpleLiteralFeeder
{
    public:
    typedef typename ComputationContext::literal_type literal_type;

    simpleLiteralFeeder(ComputationContext& _ctx) :
        idx(1),
        varBound(_ctx.numVars)
    {
    }

    literal_type getLiteral() {
        return (varBound >= idx) ? idx++ : 0;
    }
    
    TriBool getValuation(const literal_type) const {
        return TRUE;
    }
        
    literal_type idx;
    literal_type varBound;
};

/*
class VSIDSLiteralFeeder
{
    VarsFeeder(const uint32_t& varsQnty) : occur(varsQnty << 1, 0), varsQueue()
    {
        varsQueue.reserve(varsQnty << 1);
        iota(varsQueue.begin(), varsQueue.end(), -varsQnty);

    }

    inline void addOccurence(const int32_t idx)
    {
        occur[idx]++;
    }

    void reprocessCurrentState()
    {
        make_heap(varsQueue.begin(), varsQueue.end(),
                [&](const int32_t& idxa, const int32_t& idxb)
                {
                return occur[idxa] < occur[idxb];
                });
        return varsQueue.front();
    }

    int32_t getNextVar() const
    {
        return 0;
    }

    std::vector<int32_t> occur;
    std::vector<int32_t> varsQueue;
};
*/
#endif // _FEEDER_H
