#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "nTrix.h"
#include "poisson_solver.h"
#include <cmath>
#include <ctime>

class cholesky: public poisson_solver<cholesky>
{
  public:
    virtual nTrix<float> operator()(const nTrix<char>& data, float step) const override;
    void print(std::ostream& out, const nTrix<float>& data) const noexcept override;
};

#endif
