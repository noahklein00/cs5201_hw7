#include "cholesky.h"

nTrix<float> cholesky::operator()(const nTrix<char>& data, float step) const
{
  //x and b are converted to vectors
  nTrix<float> A(data.rows() * data.cols(), data.rows() * data.cols());
  nTrix<float> solution(data.rows(), data.cols());
  nTrix<float> L(A.rows(), A.cols());
  vector<float> x(A.rows());
  vector<float> y(A.rows());
  vector<float> b(A.rows());
  float temp;
  int i = 0;
  int j = 0;
  int k = 0;
  const int SIZE = L.rows();
  const int COLSIZE = data.cols();

  //filling the x vector with values
  for(i = data.rows()-1; i >= 0; --i)
  {
    for(j = 0; j < data.cols(); ++j)
    {
      if(data(i,j) == 'W')
      {
        x[k] = 0;
      }
      else if(data(i,j) == 'B')
      {
        x[k] = 1;
      }
      else
      {
        throw(std::invalid_argument("Invalid pixel character"));
      }
      ++k;
    }
  }

  //filling the b vector with values
  for(i = 0; i < SIZE; ++i)
  {
    b[i] = step;
  }

  for(i = 0; i < A.rows(); i++)
  {
    if(i <= (COLSIZE + 1))
    {
      j = 0;
    }
    else
    {
      j = i - (COLSIZE + 1);
    }
    for(; j < A.rows(); j++)
    {
      if(i == j)
      {
        A(i,j) = 1.0;
      }
      else if(i == j-COLSIZE)
      {
        A(i,j) = -.25;
      }
      else if(i == j+COLSIZE)
      {
        A(i,j) = -.25;
      }
      else if((i == j-1) && (i+1)%(COLSIZE) != 0)
      {
        A(i,j) = -.25;
      }
      else if((i == j+1) && (i)%(COLSIZE) != 0)
      {
        A(i,j) = -.25;
      }
      else
      {
        A(i,j) = 0.0;
      }
    }
  }

  for(i = 0; i < SIZE; ++i)
  {
    if(x[i] == 0)
    {
      for(j = 0; j < SIZE; ++j)
      {
        if(i != j)
        {
          A(i,j) = 0;
          A(j,i) = 0;
        }
      }
    }
  }

  for(;i < SIZE; ++i)
  {
    for(;j < SIZE; ++j)
    {
      L(i,j) = 0;
    }
  }

  for(i = 0; i < SIZE; ++i)
  {
    if(i <= (COLSIZE + 1))
    {
      j = 0;
    }
    else
    {
      j = i - (COLSIZE + 1);
    }

    for(; j <= i; ++j)
    {
      if(i <= (COLSIZE + 1))
      {
        k = 0;
      }
      else
      {
        k = i - (COLSIZE + 1);
      }

      if(i == j)
      {
        for(; k < j; ++k)
        {
          temp += std::pow(L(i,k),2);
        }
        L(i,j) = std::sqrt(A(j,j) - temp);
      }
      else
      {
        for(; k < j; ++k)
        {
          temp += (L(i,k) * L(j,k));
        }
        L(i,j) = (1.0/L(j,j)) * (A(i,j) - temp);
      }
      temp = 0;
    }
  }

  for(i = 0; i < SIZE; ++i)
  {
    if(x[i] != 0)
    {
      if(i <= COLSIZE)
      {
        j = 0;
      }
      else
      {
        j = i - COLSIZE;
      }
      for(; j < i; ++j)
      {
        temp += L(i,j) * y[j];
      }
      y[i] = (b[i] - temp)/L(i,i);
      temp = 0;
    }
  }

  for(i = SIZE-1; i >= 0; --i)
  {
    if(x[i] != 0)
    {
      if(i >= SIZE - COLSIZE - 1)
      {
        j = 0;
      }
      else
      {
        j = i + COLSIZE;
      }
      for(; j > i; --j)
      {
        temp += L(j,i) * x[j];
      }
      x[i] = (y[i] - temp)/L(i,i);
      temp = 0;
    }
  }

  i = 0;
  j = 0;
  k = 0;

  for(i = solution.rows()-1; i >= 0; --i)
  {
    for(j = 0; j < solution.cols(); ++j)
    {
      solution(i,j) = x[k];
      ++k;
    }
  }

  return solution;
}

void cholesky::print(std::ostream& out, const nTrix<float>& data) const noexcept
{
	for(int x = 0; x < data.rows(); x++)
	{
		for(int y = 0; y < data.cols(); y++)
		{
			out << data(x, y) << ",";
		}
		if(x < data.rows() - 1)
		{
			out << std::endl;
		}
	}
}
