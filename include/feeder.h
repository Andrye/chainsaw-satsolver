#ifndef _FEEDER_H
#define _FEEDER_H

#include <algorithm>
#include <numeric>
#include <vector>
/*
class simpleVarsFeeder
{
    simpleVarsFeeder(const uint32_t varsQnty) {}

};

class VSIDSVarsFeeder
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
