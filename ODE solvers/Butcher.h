#pragma once

#include <iostream>

#include "Vector.h"

using namespace std;

namespace Solver {
	struct ButcherFixed
	{
		using ild = initializer_list<double>;

		ButcherFixed(size_t step_count, ild A, initializer_list<ild> B, ild C);
		ButcherFixed(const ButcherFixed& self);
		ButcherFixed(ButcherFixed&& self) noexcept;

		~ButcherFixed();

		Vector get_dx(fx dynamics, double current_time, Vector current, double dt);

		ButcherFixed& operator=(const ButcherFixed& self);
		ButcherFixed& operator=(ButcherFixed&& self) noexcept;

		double* A;
		double** B;
		double* C;

		size_t step_count;
	};
}
