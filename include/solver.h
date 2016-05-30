#ifndef _SOLVER_H
#define _SOLVER_H

#include "ioutils.h"

template <typename IO> //, typename ClauseType, typename ValuationType, typename UnitPropagator, typename VariableFeeder>
class _solver
{
    public:
        _solver() {}
        void solve(){}
        void preprocess(){}

        int32_t numVars;
        int32_t numClauses;
};

typedef _solver<cdimacsIO> solver;

#endif // _SOLVER_H
