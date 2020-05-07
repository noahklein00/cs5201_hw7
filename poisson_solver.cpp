#include "poisson_solver.h"

void poisson_solver::print(std::ostream& out, const nTrix<float>& data)
                                                                  const noexcept
{
	for(int x = 1; x < data.rows() - 1; x++)
	{
		for(int y = 1; y < data.cols() - 1; y++)
		{
			out << data(x, y) << ",";
		}
		if(x < data.rows() - 2)
		{
			out << std::endl;
		}
	}
}