#include "FixedStepSolver.h"

namespace Solver {
    tuple<double, Vector> FixedStepSolver::Update(fx dynamics, double current_time, Vector current)
    {
        double next_time = current_time + this->dt;
        auto next = this->algorithm(dynamics, current_time, current);

        return { next_time, next };
    }
    double FixedStepSolver::get_dt()
    {
        return this->dt;
    }
    void FixedStepSolver::set_dt(double dt)
    {
        this->dt = dt;
    }
}
