#pragma once
#include "FixedStepSolver.h"

namespace Solver {
    class Euler : public FixedStepSolver
    {
    public:
        Euler(double dt):FixedStepSolver(
            dt, 
            {
                2,
                {0., 1.},
                {{}, {1.}},
                {0., 1.}
            }) {};
    };
}
