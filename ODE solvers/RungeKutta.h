#pragma once
#include "FixedStepSolver.h"

namespace Solver {
    class RungeKutta : public FixedStepSolver
    {
    public:
        RungeKutta(double dt) :FixedStepSolver(dt) {};
        ~RungeKutta() {};

        // FixedStepSolver을(를) 통해 상속됨
        virtual Vector algorithm(fx dynamics, double current_time, Vector current) override;
    };
}
