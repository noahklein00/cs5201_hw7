#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "nTrix.h"
#include <cmath>
#include <ctime>

class cholesky
{
  public:
    vector<float> operator()(const nTrix<float>& A, vector<float>& x, const vector<float>& b);
};

#endif
