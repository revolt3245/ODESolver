#pragma once
#include "FixedStepSolver.h"

namespace Solver {
    class Euler : public FixedStepSolver
    {
    public:
        Euler(double dt):FixedStepSolver(dt) {};
        // FixedStepSolver을(를) 통해 상속됨
        virtual Vector algorithm(fx dynamics, double current_time, Vector current) override;
    };
}
