#include <iostream>
#include <tuple>
#include <chrono>
#include <fstream>

#include <crtdbg.h>

#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "Vector.h"
#include "RungeKutta.h"
#include "Butcher.h"

using namespace std;
using namespace Solver;

Vector dynamics(double time, Vector x);

void test() {
	double t = 0;
	Vector x = { 2.0, 0.0 };

	auto solver = RungeKutta(1. / 1000);

	for (auto i = 0; i < 10000; i++) {
		auto [ttemp, xtemp] = solver.Update(dynamics, t, x);
		t = ttemp;
		x = xtemp;

		//cout << x << "\n";
	}
}

int main() {
	test();

	_CrtDumpMemoryLeaks();

	return 0;
}

Vector dynamics(double time, Vector x) {
	Vector dx(2);
	dx[0] = x[1];
	dx[1] = (1 - pow(x[0], 2)) * x[1] - x[0];

	return dx;
}