#pragma once
#include "Solver.h"
#include "Butcher.h"

namespace Solver {
	class FixedStepSolver : public Solver
	{
	public:
		FixedStepSolver(double dt, ButcherFixed tableu) :Solver(), dt(dt), tableu(tableu) {};
		~FixedStepSolver() {};

		// Solver을(를) 통해 상속됨
		virtual tuple<double, Vector> Update(fx dynamics, double current_time, Vector current) override;

		double get_dt();
		void set_dt(double dt);
	private:
		double dt;

		ButcherFixed tableu;
	};
}
