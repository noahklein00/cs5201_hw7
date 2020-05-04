#include "cholesky.h"

vector<float> cholesky::operator()(const nTrix<float>& A, vector<float>& x, const vector<float>& b)
{
  nTrix<float> L(A.rows(), A.cols());
  //nTrix<float> U(A.rows(), A.cols());
  vector<float> y(A.rows());
  float temp = 0;

  for(int i = 0; i < L.rows(); i++)
  {
    for(int j = 0; j < L.cols(); j++)
    {
      L(i,j) = float(0.0);
      //U(i,j) = float(0.0);
    }
  }

  int s = 0;
  int t = 0;
  int r = 0;
  //start_s = clock();
  for(; s < L.rows(); ++s)
  {
    if(s <= sqrt(L.rows())+1)
    {
      t=0;
    }
    else
    {
      t = s - (sqrt(L.rows())+1);
    }
    //t = 0;
    for(; t <= s; ++t)
    {
      //r = 0;
      if(s <= sqrt(L.rows())+1)
      {
        r=0;
      }
      else
      {
        r = s - (sqrt(L.rows())+1);
      }
      if(s == t)
      {
        for(; r < t; ++r)
        {
          temp += std::pow(L(s,r),2);
        }
        L(s,t) = std::sqrt(A(t,t) - temp);
      }
      else
      {
        for(; r < t; ++r)
        {
          temp += (L(s,r) * L(t,r));
        }
        L(s,t) = (1.0/L(t,t)) * (A(s,t) - temp);
      }
      temp = 0;
    }
  }

  //U = L.transpose();
  for(int i = 0; i < y.size(); i++)
  {
    if(x[i] != 0)
    {
      for(int j = 0; j < i; j++)
      {
        temp += L(i,j) * y[j];
      }
      y[i] = (b[i] - temp)/L(i,i);
      temp = 0;
    }
  }

  for(int i = x.size()-1; i >= 0; i--)
  {
    if(x[i] != 0)
    {
      for(int j = x.size()-1; j > i; j--)
      {
        temp += L(j,i) * x[j];
      }
      x[i] = (y[i] - temp)/L(i,i);
      temp = 0;
    }
  }
  return x;
}
