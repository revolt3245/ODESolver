#pragma once

#include <iostream>
#include <functional>
#include <tuple>

#include "Vector.h"
using namespace std;

namespace Solver {
	class Solver
	{
	public:
		Solver() {};

		virtual tuple<double, Vector> Update(fx dynamics, double current_time, Vector current) = 0;
	};
}
