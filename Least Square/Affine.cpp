#include "Affine.h"

namespace LeastSquare {
	Affine::Affine()
	{
		this->mapping = nullptr;
		this->A = nullptr;
		this->B = 0.0;

		this->lambda = 0.0;
		this->size_A = 0;
	}
	Affine::Affine(ilui i_mapping, ild i_A, double B)
	{
		auto size_mapping = i_mapping.size();

		this->size_A = size_mapping;

		this->mapping = new unsigned int[size_mapping];
		this->A = new double[size_mapping];

		memcpy(this->mapping, i_mapping.begin(), size_mapping * sizeof(unsigned int));
		memcpy(this->A, i_A.begin(), size_mapping * sizeof(double));

		this->B = B;

		this->lambda = 0;
	}
	Affine::Affine(const Affine& obj)
	{
		this->size_A = obj.size_A;

		this->mapping = new unsigned int[this->size_A];
		this->A = new double[this->size_A];

		memcpy(this->mapping, obj.mapping, this->size_A * sizeof(unsigned int));
		memcpy(this->A, obj.A, this->size_A * sizeof(double));

		this->B = obj.B;
		this->lambda = obj.lambda;
	}
	Affine::Affine(Affine&& obj) noexcept
	{
		this->size_A = obj.size_A;

		this->mapping = obj.mapping;
		this->A = obj.A;
		this->B = obj.B;
		this->lambda = obj.lambda;

		obj.A = nullptr;
		obj.mapping = nullptr;
	}
	Affine::~Affine()
	{
		if (this->A != nullptr) {
			delete[] A;
		}

		if (this->mapping != nullptr) {
			delete[] mapping;
		}
	}
	void Affine::initialize()
	{
		this->lambda = 0;
	}
	void Affine::update(double* diff, double alpha)
	{
		auto res = 0.0;
		auto a_square = this->get_Asquare();

		for (auto i = 0; i < size_A; i++) {
			res -= diff[this->mapping[i]] * this->A[i];
		}

		res -= B;
		res /= a_square;

		this->lambda += alpha * res;
	}
	double Affine::get_lambda()
	{
		return this->lambda;
	}
	void Affine::get_A(double* A_out)
	{
		memcpy(A_out, this->A, this->size_A * sizeof(double));
	}
	void Affine::get_mapping(unsigned int* mapping_out)
	{
		memcpy(mapping_out, this->mapping, this->size_A * sizeof(unsigned int));
	}
	size_t Affine::get_size()
	{
		return this->size_A;
	}
	Affine& Affine::operator=(const Affine& self)
	{
		if (this->A != nullptr) {
			delete[] A;
		}
		if (this->mapping != nullptr) {
			delete[] mapping;
		}

		this->size_A = self.size_A;
		this->B = self.B;
		this->lambda = self.lambda;

		this->A = new double[this->size_A];
		this->mapping = new unsigned int[this->size_A];

		memcpy(this->A, self.A, this->size_A * sizeof(double));
		memcpy(this->mapping, self.mapping, this->size_A * sizeof(unsigned int));

		return *this;
	}
	Affine& Affine::operator=(Affine&& self) noexcept
	{
		if (this->A != nullptr) {
			delete[] A;
		}
		if (this->mapping != nullptr) {
			delete[] mapping;
		}

		this->size_A = self.size_A;
		this->B = self.B;
		this->lambda = self.lambda;
		this->A = self.A;
		this->mapping = self.mapping;

		self.A = nullptr;
		self.mapping = nullptr;

		return *this;
	}
	double Affine::get_Asquare()
	{
		double res = 0.0;

		for (auto i = 0; i < size_A; i++) {
			res += this->A[i] * this->A[i];
		}

		return res;
	}
}