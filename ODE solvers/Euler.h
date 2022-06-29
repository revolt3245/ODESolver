#pragma once
#include "FixedStepSolver.h"

namespace Solver {
    class Euler : public FixedStepSolver
    {
    public:
        Euler(double dt):FixedStepSolver(dt) {};
        // FixedStepSolver��(��) ���� ��ӵ�
        virtual Vector algorithm(fx dynamics, double current_time, Vector current) override;
    };
}
