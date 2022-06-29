#include "Vector.h"

namespace Solver {
	Vector::Vector()
	{
		this->X = new double[page_data];
		this->dim = 0;

		this->alloc_page = 0;
	}
	Vector::Vector(initializer_list<double> Xin)
	{
		this->dim = Xin.size();
		size_t alloc_size = this->dim / page_data + (bool)(this->dim % page_data);

		this->X = new double[alloc_size * page_data];

		memcpy(this->X, Xin.begin(), this->dim * sizeof(double));

		this->alloc_page = alloc_size;
	}
	Vector::Vector(size_t size)
	{
		this->dim = size;
		size_t alloc_size = this->dim / page_data + (bool)(this->dim % page_data);

		this->X = new double[alloc_size * page_data];
		fill(X, X + alloc_size, 0);

		this->alloc_page = alloc_size;
	}
	Vector::Vector(const Vector& self)
	{
		this->dim = self.dim;
		this->alloc_page = self.alloc_page;

		this->X = new double[this->alloc_page * page_data];

		memcpy(this->X, self.X, this->dim * sizeof(double));
	}
	Vector::Vector(Vector&& self) noexcept
	{
		this->dim = self.dim;
		this->X = self.X;
		this->alloc_page = self.alloc_page;

		self.X = nullptr;
	}
	Vector::~Vector()
	{
		if (this->X != nullptr) {
			delete[] X;
			X = nullptr;
		}
	}
	Vector Vector::operator+(const Vector& obj)
	{
		if (this->dim != obj.dim) {
			cerr << "two vectors have different dimension\n";

			return Vector(this->dim);
		}

		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] + obj.X[i];
		}

		return res;
	}
	Vector Vector::operator-(const Vector& obj)
	{
		if (this->dim != obj.dim) {
			cerr << "two vectors have different dimension\n";

			return Vector(this->dim);
		}

		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] - obj.X[i];
		}

		return res;
	}
	Vector Vector::operator*(const Vector& obj)
	{
		if (this->dim != obj.dim) {
			cerr << "two vectors have different dimension\n";

			return Vector(this->dim);
		}

		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] * obj.X[i];
		}

		return res;
	}
	Vector Vector::operator/(const Vector& obj)
	{
		if (this->dim != obj.dim) {
			cerr << "two vectors have different dimension\n";

			return Vector(this->dim);
		}

		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] / obj.X[i];
		}

		return res;
	}
	Vector Vector::operator+(const double& num)
	{
		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] + num;
		}

		return res;
	}
	Vector Vector::operator-(const double& num)
	{
		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] - num;
		}

		return res;
	}
	Vector Vector::operator*(const double& num)
	{
		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] * num;
		}

		return res;
	}
	Vector Vector::operator/(const double& num)
	{
		Vector res(this->dim);

		for (int i = 0; i < this->dim; i++) {
			res.X[i] = this->X[i] / num;
		}

		return res;
	}
	Vector& Vector::operator=(const Vector& obj)
	{
		this->dim = obj.dim;
		size_t alloc_size = this->dim / page_data + (bool)(this->dim % page_data);
		if (this->alloc_page != alloc_size) {
			this->alloc_page = alloc_size;

			delete[] this->X;

			this->X = new double[alloc_page * page_data];
		}

		memcpy(this->X, obj.X, dim * sizeof(double));

		return *this;
	}
	Vector& Vector::operator=(Vector&& obj) noexcept
	{
		this->dim = obj.dim;
		this->alloc_page = obj.alloc_page;

		if (this->X != nullptr) {
			delete[] this->X;
		}
		this->X = obj.X;
		obj.X = nullptr;

		return *this;
	}
	double& Vector::operator[](size_t idx)
	{
		return this->X[idx];
	}
	double* Vector::get_data()
	{
		return this->X;
	}
	size_t Vector::get_dim()
	{
		return this->dim;
	}
	ostream& operator<<(ostream& os, const Vector& obj)
	{
		for (int i = 0; i < obj.dim; i++) {

			os << obj.X[i];
			if (i != obj.dim - 1)os << ", ";
		}

		return os;
	}
	Vector operator+(const double& num, const Vector& obj)
	{
		Vector res(obj.dim);

		for (int i = 0; i < obj.dim; i++) {
			res.X[i] = num + obj.X[i];
		}

		return res;
	}
	Vector operator-(const double& num, const Vector& obj)
	{
		Vector res(obj.dim);

		for (int i = 0; i < obj.dim; i++) {
			res.X[i] = num - obj.X[i];
		}

		return res;
	}
	Vector operator*(const double& num, const Vector& obj)
	{
		Vector res(obj.dim);

		for (int i = 0; i < obj.dim; i++) {
			res.X[i] = num * obj.X[i];
		}

		return res;
	}
	Vector operator/(const double& num, const Vector& obj)
	{
		Vector res(obj.dim);

		for (int i = 0; i < obj.dim; i++) {
			res.X[i] = num / obj.X[i];
		}

		return res;
	}
}