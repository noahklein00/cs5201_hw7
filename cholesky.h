#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "nTrix.h"
#include "poisson_solver.h"
#include <cmath>
#include <ctime>

class cholesky: public poisson_solver
{
  public:
    virtual nTrix<float> operator()(const nTrix<char>& data, float step) const;
    //vector<float> operator()(const nTrix<float>& A, vector<float>& x, const vector<float>& b);
    //virtual void print(std::ostream& out) const noexcept;
    //friend std::ostream& operator<<(std::ostream& out, const cholesky& i) noexcept;
};

#endif
