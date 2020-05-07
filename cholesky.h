#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "nTrix.h"
#include "poisson_solver.h"
#include <cmath>
#include <ctime>

class cholesky: public poisson_solver
{
  private:
    nTrix<float> m_solution;

  public:
    cholesky(const nTrix<char>& input, const float m_step);
    //vector<float> operator()(const nTrix<float>& A, vector<float>& x, const vector<float>& b);
    virtual const nTrix<float>& getMat() const noexcept;
    virtual void print(std::ostream& out) const noexcept;
    friend std::ostream& operator<<(std::ostream& out, const cholesky& i) noexcept;
};

#endif
