#pragma once

#include <iostream>

using namespace std;

namespace LeastSquare {
	using ilui = initializer_list<unsigned int>;
	using ild = initializer_list<double>;

	class Affine
	{
	public:
		// constructor
		Affine();
		Affine(ilui i_mapping, ild i_A, double B);
		Affine(const Affine& obj);
		Affine(Affine&& obj) noexcept;

		//destructor
		~Affine();

		// initializer
		void initialize();

		// update
		void update(double* diff, double alpha);

		// getter
		double get_lambda();
		void get_A(double* A_out);
		void get_mapping(unsigned int* mapping_out);
		size_t get_size();

		//assign
		Affine& operator=(const Affine& self);
		Affine& operator=(Affine&& self) noexcept;
	private:
		double get_Asquare();
	private:
		unsigned int* mapping;
		double* A;
		double B;

		double lambda;

		size_t size_A;
	};
}
