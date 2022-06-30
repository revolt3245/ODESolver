#include "FixedStepSolver.h"

namespace Solver {
    tuple<double, Vector> FixedStepSolver::Update(fx dynamics, double current_time, Vector current)
    {
        double next_time = current_time + this->dt;
        auto dx = this->tableu.get_dx(dynamics, current_time, current, this->dt);
        auto next = current + dx * this->dt;

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
