#include "sat_include_all.h"
#include <iostream>

int main()
{
    cdimacsIO io(std::cin, std::cout, std::cerr);

    solver<cdimacsIO,
           clause,
           valuation<TriBool>,
           simpleLiteralFeeder< computation_context <clause, valuation<TriBool>>>
          > solver(io);
    solver.fillFormula();
    solver.run();
}
