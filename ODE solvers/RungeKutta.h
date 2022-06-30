#pragma once
#include "FixedStepSolver.h"

namespace Solver {
    class RungeKutta : public FixedStepSolver
    {
    public:
        RungeKutta(double dt) :FixedStepSolver(
            dt,
            {
                4, 
                { 0., 0.5, 0.5, 1.0 }, 
                { {}, {0.5},{0.0, 0.5}, {0.0, 0.0, 1.0} }, 
                { 1. / 6, 2. / 6, 2. / 6, 1. / 6 }
            }) {};
        ~RungeKutta() {};
    };
}
