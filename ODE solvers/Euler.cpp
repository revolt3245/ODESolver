#include "Euler.h"

namespace Solver {
    Vector Euler::algorithm(fx dynamics, double current_time, Vector current)
    {
        auto dx = dynamics(current_time, current);
        auto dt = this->get_dt();

        auto Vnext = current + dx * dt;
        return Vnext;
    }
}