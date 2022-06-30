#pragma once

#include <iostream>
#include <functional>

#include <crtdbg.h>

#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace std;

namespace Solver {
	const size_t page_data = 32;

	struct Vector
	{
		//constructor
		Vector();
		Vector(initializer_list<double> X);
		Vector(size_t size);

		// copy
		Vector(const Vector& self);
		// move
		Vector(Vector&& self) noexcept;

		// destructor
		~Vector();

		// display
		friend ostream& operator<<(ostream& os, const Vector& obj);

		// arithmatic
		Vector operator+(const Vector& obj);
		Vector operator-(const Vector& obj);
		Vector operator*(const Vector& obj);
		Vector operator/(const Vector& obj);

		Vector operator+(const double& num);
		Vector operator-(const double& num);
		Vector operator*(const double& num);
		Vector operator/(const double& num);

		friend Vector operator+(const double& num, const Vector& obj);
		friend Vector operator-(const double& num, const Vector& obj);
		friend Vector operator*(const double& num, const Vector& obj);
		friend Vector operator/(const double& num, const Vector& obj);

		// assign
		Vector& operator=(const Vector& obj);
		Vector& operator=(Vector&& obj) noexcept;

		// indexing
		double& operator[](size_t idx) const;

		// Vector operations
		friend double dot(const Vector& v1, const Vector& v2);
		friend double norm(const Vector& v1);

		//append
		Vector& append(const double& num);
		Vector& append(const Vector& v);

		//getter
		double* get_data();
		size_t get_dim();
	private:
		//member
		double* X;
		size_t dim;

		size_t alloc_page;
	};

	using fx = function<Vector(double, Vector)>;
}

