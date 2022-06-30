#include "Butcher.h"

namespace Solver {
	ButcherFixed::ButcherFixed(size_t step_count, ild A, initializer_list<ild> B, ild C)
	{
		// memory initialize
		this->A = new double[step_count];
		this->B = new double* [step_count];
		this->C = new double[step_count];

		for (auto i = 0; i < step_count; i++) {
			this->B[i] = new double[i];
		}

		// size
		this->step_count = step_count;

		memcpy(this->A, A.begin(), step_count * sizeof(double));
		memcpy(this->C, C.begin(), step_count * sizeof(double));
		for (auto i = 0; i < step_count; i++) {
			memcpy(this->B[i], (B.begin() + i)->begin(), i * sizeof(double));
		}
	}
	ButcherFixed::ButcherFixed(const ButcherFixed& self)
	{
		this->step_count = self.step_count;
		// new state;
		this->A = new double[this->step_count];
		this->B = new double* [this->step_count];
		this->C = new double[this->step_count];

		memcpy(this->A, self.A, this->step_count * sizeof(double));

		for (auto i = 0; i < this->step_count; i++) {
			this->B[i] = new double[i];

			memcpy(this->B[i], self.B[i], i * sizeof(double));
		}

		memcpy(this->C, self.C, step_count * sizeof(double));
	}
	ButcherFixed::ButcherFixed(ButcherFixed&& self) noexcept
	{
		this->step_count = self.step_count;

		this->A = self.A;
		this->B = self.B;
		this->C = self.C;

		self.A = nullptr;
		self.B = nullptr;
		self.C = nullptr;
	}
	ButcherFixed::~ButcherFixed()
	{
		if (this->A != nullptr) {
			delete[] this->A;
			A = nullptr;
		}

		if (this->B != nullptr) {
			for (auto i = 0; i < this->step_count; i++) {
				if (this->B[i] != nullptr) {
					delete[] this->B[i];
					this->B[i] = nullptr;
				}
			}

			delete[] this->B;
			this->B = nullptr;
		}

		if (this->C != nullptr) {
			delete[] this->C;
			this->C = nullptr;
		}
	}
	Vector ButcherFixed::get_dx(fx dynamics, double current_time, Vector current, double dt)
	{
		auto dxs = new Vector[this->step_count];
		auto dx = Vector(current.get_dim());

		double time_temp;
		Vector state_temp = Vector(current.get_dim());

		for (auto i = 0; i < this->step_count; i++) {
			if (i == 0) {
				dxs[i] = dynamics(current_time, current);
			}
			else {
				time_temp = current_time + this->A[i];
				state_temp = current;
				for (auto j = 0; j < i; j++) {
					state_temp = state_temp + dxs[j] * B[i][j] * dt;
				}
				dxs[i] = dynamics(time_temp, state_temp);
			}

			dx = dx + dxs[i] * C[i];
		}

		delete[] dxs;

		return dx;
	}
	ButcherFixed& ButcherFixed::operator=(const ButcherFixed& self)
	{
		// clear
		if (this->A != nullptr) {
			delete[] this->A;
		}

		if (this->B != nullptr) {
			for (auto i = 0; i < this->step_count; i++) {
				if (this->B[i] != nullptr) {
					delete[] this->B[i];
				}
			}
			delete[] this->B;
		}

		if (this->C != nullptr) {
			delete[] this->C;
		}

		this->step_count = self.step_count;
		// new state;
		this->A = new double[this->step_count];
		this->B = new double* [this->step_count];
		this->C = new double[this->step_count];

		memcpy(this->A, self.A, this->step_count * sizeof(double));

		for (auto i = 0; i < this->step_count; i++) {
			this->B[i] = new double[i];

			memcpy(this->B[i], self.B[i], i * sizeof(double));
		}

		return *this;
	}
	ButcherFixed& ButcherFixed::operator=(ButcherFixed&& self) noexcept
	{
		// clear
		if (this->A != nullptr) {
			delete[] this->A;
		}

		if (this->B != nullptr) {
			for (auto i = 0; i < this->step_count; i++) {
				if (this->B[i] != nullptr) {
					delete[] this->B[i];
				}
			}
			delete[] this->B;
		}

		if (this->C != nullptr) {
			delete[] this->C;
		}

		this->step_count = self.step_count;

		this->A = self.A;
		this->B = self.B;
		this->C = self.C;

		self.A = nullptr;
		self.B = nullptr;
		self.C = nullptr;

		return *this;
	}
}