#ifndef _SOLVER_H
#define _SOLVER_H

#include "ioutils.h"

template <typename IO>
class _solver
{
    public:
        _solver() {}
        void solve(){}
};

typedef _solver<cdimacsIO> solver;

#endif // _SOLVER_H
