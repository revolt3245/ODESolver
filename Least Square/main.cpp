#include <iostream>

#include "Affine.h"

using namespace std;
using namespace LeastSquare;

int main() {
	auto iter = 100;
	double alpha = 0.1;

	double X[3] = { 0.0, 0.0, 0.0 };

	Affine x[2];
	x[0] = { {0, 1}, {1, 1}, 1 };
	x[1] = { {0, 1, 2}, {1, 1, 1}, 1 };

	for (auto i = 0; i < 2; i++) {
		x[i].initialize();
	}

	for (auto i = 0; i < iter; i++) {
		for (auto j = 0; j < 2; j++) {
			x[j].update(X, alpha);
		}

		for (auto j = 0; j < 3; j++) {
			X[j] = 0;
		}

		for (auto j = 0; j < 2; j++) {
			auto size_A = x[j].get_size();
			auto lambda = x[j].get_lambda();

			auto A = new double[size_A];
			auto mapping = new unsigned int[size_A];

			x[j].get_A(A);
			x[j].get_mapping(mapping);

			for (auto k = 0; k < size_A; k++) {
				X[mapping[k]] += A[k] * lambda;
			}

			delete[] A, mapping;
		}

		for (auto j = 0; j < 3; j++) {
			cout << X[j] << " ";
		}
		cout << "\n";
	}
	return 0;
}