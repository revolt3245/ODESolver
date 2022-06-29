#include "RungeKutta.h"

namespace Solver {
	Vector RungeKutta::algorithm(fx dynamics, double current_time, Vector current)
	{
		auto dt = this->get_dt();

		auto dx1 = dynamics(current_time, current);
		auto dx2 = dynamics(current_time + dt / 2, current + dx1 * dt / 2);
		auto dx3 = dynamics(current_time + dt / 2, current + dx2 * dt / 2);
		auto dx4 = dynamics(current_time + dt, current + dx3 * dt);

		auto dx = (dx1 + dx2 * 2 + dx3 * 2 + dx4) / 6;

		return current + dx * dt;
	}
}