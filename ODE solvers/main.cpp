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

using namespace std;
using namespace Solver;

Vector dynamics(double time, Vector x);

void test() {
	// file
	ofstream file("data.csv", 'w');
	file.precision(5);
	cout.precision(5);

	file.setf(ios::fixed);
	cout.setf(ios::fixed);

	// local solver
	Vector X = { 2.0, 0. };
	auto solver = RungeKutta(1. / 1000);
	double t = 0.0;

	double elapses = 0.0;

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {
		auto start = chrono::high_resolution_clock::now();
		auto [ttemp, Xtemp] = solver.Update(dynamics, t, X);
		auto elapse = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();

		t = ttemp;
		X = Xtemp;

		file << t << ", " << X << "\n";

		/*
		if (i % 100 == 99) {
			cout << X << "\n";
		}
		*/

		elapses += elapse;
	}
	cout << elapses / 100000 << " us\n";
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