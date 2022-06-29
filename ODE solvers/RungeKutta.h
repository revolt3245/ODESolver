#pragma once
#include "FixedStepSolver.h"

namespace Solver {
    class RungeKutta : public FixedStepSolver
    {
    public:
        RungeKutta(double dt) :FixedStepSolver(dt) {};
        ~RungeKutta() {};

        // FixedStepSolver��(��) ���� ��ӵ�
        virtual Vector algorithm(fx dynamics, double current_time, Vector current) override;
    };
}
