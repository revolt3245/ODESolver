#pragma once
#include "Solver.h"

namespace Solver {
	class FixedStepSolver : public Solver
	{
	public:
		FixedStepSolver(double dt) :Solver(), dt(dt) {};
		~FixedStepSolver() {};

		// Solver��(��) ���� ��ӵ�
		virtual tuple<double, Vector> Update(fx dynamics, double current_time, Vector current) override;

		virtual Vector algorithm(fx dynamics, double current_time, Vector current) = 0;

		double get_dt();
		void set_dt(double dt);
	private:
		double dt;
	};
}
