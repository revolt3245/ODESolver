#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;

const double err = 1e-6;

// (A, B, Q, R) -> P
void qr(double* Q, double* R, double* A, size_t Ar, size_t Ac);
void matmul(double* R, double* A, double* B, size_t Ar, size_t Br, size_t Bc);
void inverse(double* Ainv, double* A, size_t s);

void eig(double* V, double* D, double* A, size_t Ar, unsigned int n_iter = 10);
void print_matrix(double* A, size_t Ar, size_t Ac);
void sparsify(double* A, size_t Ar, size_t Ac, double threshold = err);

void dare(double* P, double* K, double* A, double* B, double* Q, double* R, size_t nx, size_t nu, unsigned int n_iter = 100);

void plusmat(double* A, double* B, size_t Ar, size_t Ac);
void minusmat(double* A, double* B, size_t Ar, size_t Ac);

void transpose(double* R, double* A, size_t Ar, size_t Ac);

void quadratic(double* R, double* A, double* Q, size_t Ar, size_t Ac);
//AtQB
void quadratic(double* R, double* A, double* B, double* Q, size_t Ac, size_t Br, size_t Bc);

int main() {
	size_t nx = 2, nu = 1;
	double A[4] = { 0.9999, 0.0099, -0.0297, 0.9801 };
	double B[2] = { 0, 0.0099 };
	double Q[4] = { 1, 0, 0, 1 };
	double R[1] = { 1 };

	auto P = new double[nx * nx];
	auto K = new double[nu * nx];
	
	auto start = chrono::high_resolution_clock::now();
	dare(P, K, A, B, Q, R, nx, nu);
	auto elapse = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();

	cout << "P\n";
	print_matrix(P, nx, nx);
	cout << "\nK\n";
	print_matrix(K, nu, nx);
	cout << "\nelapse : " << elapse << " us\n";

	delete[] P, K;

	return 0;
}

void qr(double* Q, double* R, double* A, size_t Ar, size_t Ac) {
	// copy A
	memcpy(Q, A, Ar * Ac * sizeof(double));
	fill(R, R + Ar * Ac, 0);

	auto Avec = new double[Ar];
	for (auto i = 0; i < Ac; i++) {
		// length
		double length = 0.0;
		for (auto j = 0; j < Ar; j++) {
			length += Q[j * Ac + i] * Q[j * Ac + i];
		}

		R[i * Ac + i] = sqrt(length);

		//normalize
		for (auto j = 0; j < Ar; j++) {
			Q[j * Ac + i] /= R[i * Ac + i];
		}

		// gram-schmidt process
		for (auto j = i + 1; j < Ac; j++) {
			// projection
			for (auto k = 0; k < Ar; k++) {
				R[i * Ac + j] += Q[k * Ac + i] * Q[k * Ac + j];
			}

			for (auto k = 0; k < Ar; k++) {
				Q[k * Ac + j] -= R[i * Ac + j] * Q[k * Ac + i];
			}
		}
	}
}

void matmul(double* R, double* A, double* B, size_t Ar, size_t Br, size_t Bc) {
	// initialize
	fill(R, R + Ar * Bc, 0);

	for (auto i = 0; i < Ar; i++) {
		for (auto j = 0; j < Br; j++) {
			for (auto k = 0; k < Bc; k++) {
				R[i * Bc + k] += A[i * Br + j] * B[j * Bc + k];
			}
		}
	}
}

void inverse(double* Ainv, double* A, size_t s) {
	// copy A
	auto Acpy = new double[s * s];
	auto Ainvcpy = new double[s * s];
	auto pivots = new size_t[s];

	memcpy(Acpy, A, s * s * sizeof(double));
	
	// Ainv = I
	fill(Ainvcpy, Ainvcpy + s * s, 0);
	for (size_t i = 0; i < s; i++) {
		Ainvcpy[i * s + i] = 1;
	}

	// gauss jordan
	// row
	for (size_t i = 0; i < s; i++) {
		// pivot search
		size_t pivot = -1;
		for (size_t j = 0; j < s; j++) {
			if (abs(Acpy[i * s + j]) >= err) {
				pivot = j;
				break;
			}
		}
		if (pivot == -1) {
			delete[] Acpy;
			return;
		}

		double Apivot = Acpy[i * s + pivot];
		// division
		for (size_t j = 0; j < s; j++) {
			Acpy[i * s + j] /= Apivot;
			Ainvcpy[i * s + j] /= Apivot;
		}

		// row reduction
		for (size_t j = 0; j < s; j++) {
			if (j == i)continue;

			Apivot = Acpy[j * s + pivot];
			if (abs(Apivot) < err)continue;

			for (size_t k = 0; k < s; k++) {
				Acpy[j * s + k] -= Apivot * Acpy[i * s + k];
				Ainvcpy[j * s + k] -= Apivot * Ainvcpy[i * s + k];
			}
		}
		pivots[i] = pivot;
	}
	for (auto i = 0; i < s; i++) {
		memcpy(Ainv + pivots[i] * s, Ainvcpy + i * s, s * sizeof(double));
	}
	delete[] Acpy;
	delete[] Ainvcpy;
	delete[] pivots;
}

void eig(double* V, double* D, double* A, size_t Ar, unsigned int n_iter) {
	auto Q0 = new double[Ar * Ar];
	auto R0 = new double[Ar * Ar];
	auto A0 = new double[Ar * Ar];
	auto Vtemp = new double[Ar * Ar];

	fill(V, V + Ar * Ar, 0);
	for (auto i = 0; i < Ar; i++) {
		V[i * Ar + i] = 1;
	}

	memcpy(A0, A, Ar * Ar * sizeof(double));

	for (auto iter = 0u; iter < n_iter; iter++) {
		//qr fact
		qr(Q0, R0, A0, Ar, Ar);

		// update Ak
		matmul(A0, R0, Q0, Ar, Ar, Ar);

		// update D
		matmul(Vtemp, V, Q0, Ar, Ar, Ar);
		memcpy(V, Vtemp, Ar * Ar * sizeof(double));
	}
	memcpy(D, A0, Ar * Ar * sizeof(double));

	sparsify(V, Ar, Ar);
	sparsify(D, Ar, Ar);

	delete[] Q0, R0, A0, Vtemp;
}

void print_matrix(double* A, size_t Ar, size_t Ac) {
	for (auto i = 0; i < Ar; i++) {
		for (auto j = 0; j < Ac; j++) {
			cout << A[i * Ac + j] << " ";
		}
		cout << "\n";
	}
}

void sparsify(double* A, size_t Ar, size_t Ac, double threshold) {
	for (auto i = 0; i < Ar; i++) {
		for (auto j = 0; j < Ac; j++) {
			if (abs(A[i * Ac + j]) < threshold) {
				A[i * Ac + j] = 0;
			}
		}
	}
}

void dare(double* P, double* K, double* A, double* B, double* Q, double* R, size_t nx, size_t nu, unsigned int n_iter) {
	// initialize
	memcpy(P, Q, nx * nx * sizeof(double));

	// temp
	auto Ptemp = new double[nx * nx];
	auto APA = new double[nx * nx];
	auto BPB = new double[nu * nu];
	auto BPBinv = new double[nu * nu];
	auto BPA = new double[nu * nx];

	for (auto iter = 0; iter < n_iter; iter++) {
		quadratic(APA, A, P, nx, nx);
		print_matrix(APA, nx, nx);

		quadratic(BPB, B, P, nx, nu);
		plusmat(BPB, R, nu, nu);

		inverse(BPBinv, BPB, nu);

		quadratic(BPA, B, A, P, nu, nx, nx);
		quadratic(Ptemp, BPA, BPBinv, nu, nx);

		fill(P, P + nx * nx, 0);
		plusmat(P, Q, nx, nx);
		plusmat(P, APA, nx, nx);
		minusmat(P, Ptemp, nx, nx);
	}

	matmul(K, BPBinv, BPA, nu, nu, nx);

	delete[] Ptemp, APA, BPB, BPBinv, BPA;
}

void plusmat(double* A, double* B, size_t Ar, size_t Ac) {
	for (auto i = 0; i < Ar; i++) {
		for (auto j = 0; j < Ac; j++) {
			A[i * Ac + j] = A[i * Ac + j] + B[i * Ac + j];
		}
	}
}
void minusmat(double* A, double* B, size_t Ar, size_t Ac) {
	for (auto i = 0; i < Ar; i++) {
		for (auto j = 0; j < Ac; j++) {
			A[i * Ac + j] = A[i * Ac + j] - B[i * Ac + j];
		}
	}
}

void transpose(double* R, double* A, size_t Ar, size_t Ac) {
	for (auto i = 0; i < Ar; i++) {
		for (auto j = 0; j < Ac; j++) {
			R[j * Ar + i] = A[i * Ac + j];
		}
	}
}

void quadratic(double* R, double* A, double* Q, size_t Ar, size_t Ac) {
	fill(R, R + Ac * Ac, 0);

	for (auto i = 0; i < Ac; i++) {
		for (auto j = 0; j < Ac; j++) {
			for (auto k = 0; k < Ar; k++) {
				for (auto l = 0; l < Ar; l++) {
					R[k * Ac + l] += Q[i * Ar + j] * A[k * Ar + i] * A[l * Ar + j];
				}
			}
		}
	}
}

void quadratic(double* R, double* A, double* B, double* Q, size_t Ac, size_t Br, size_t Bc) {
	fill(R, R + Ac * Bc, 0);

	for (auto i = 0; i < Ac; i++) {
		for (auto j = 0; j < Bc; j++) {
			for (auto k = 0; k < Br; k++) {
				for (auto l = 0; l < Br; l++) {
					R[i * Bc + j] += Q[k * Br + l] * A[k * Ac + i] * B[j * Bc + l];
				}
			}
		}
	}
}