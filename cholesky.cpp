/**
 * @file    cholesky.cpp
 * @author  Jeffrey Strahm and Noah Klein
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/10/20
*/

#include "cholesky.h"

void cholesky::invalArgErr(const std::string& msg) const
{
    std::cout << msg << std::endl;
    throw std::invalid_argument(msg);
}

nTrix<float> cholesky::operator()(const nTrix<char>& data, float step) const
{
  //x and b are converted to vectors.
  //A is the matrix that holds the system of equations.
  nTrix<float> A(data.rows() * data.cols(), data.rows() * data.cols());
  //solution is the matrix that holds the final matrix representation of the
  //solution vector.
  nTrix<float> solution(data.rows(), data.cols());
  //L is the lower triangular matrix that A decomposes into through cholesky
  //decomposition.
  nTrix<float> L(A.rows(), A.cols());
  //x is the vector representation of the solution to the system of equations.
  vector<float> x(A.rows());
  //y is the intermediate vector constructed while solving Ly = b and Ux = y
  //where U = L.transpose().
  vector<float> y(A.rows());
  //b is the vector of known points along the boundary that gets the forcing
  //function added to it.
  vector<float> b(A.rows());
  //temp is a variable that gets used to store temporary information when
  //solving Ly = b and Ux = y.
  float temp;
  //i,j, and k are counters that are initialized at the start to avoid
  //initializing them during the for loops. This saves a lot of time.
  int i = 0;
  int j = 0;
  int k = 0;
  //SIZE is a constant that represents the N value of the NxN matrices used.
  const int SIZE = L.rows();
  //COLSIZE is a constant that represents the number of columns in the original
  //input matrix passed.
  const int COLSIZE = data.cols();

  if (step <= 0)
  {
    const std::string err = "Step size must be greater than 1. "
                            "Passed step size: " + std::to_string(step);
    invalArgErr(err);
  }

  //filling the x vector with values
  for(i = data.rows()-1; i >= 0; --i)
  {
    for(j = 0; j < data.cols(); ++j)
    {
      //Since we know that all 'W' values have no effect we can set them equal
      //to 0.
      if(data(i,j) == 'W')
      {
        x[k] = 0;
      }
      //The 'B' values are set to a temporary placeholder of 1.
      else if(data(i,j) == 'B')
      {
        x[k] = 1;
      }
      else
      {
        //throws an error if the input matrix is not composed of B's and W's
        const std::string err = "Input character matrix is not composed of only"
                                 " B and W.";
        invalArgErr(err);
      }
      ++k;
    }
  }

  //Since we know the border will be all 0's, and that the forcing function is
  //a constant, we can set the entire b vector equal to that value.
  for(i = 0; i < SIZE; ++i)
  {
    b[i] = step;
  }

  //Filling in the values of the A matrix.
  for(i = 0; i < A.rows(); i++)
  {
    //Since we know that A will always be banded and that the bands will be
    //bound around the diagonal by +/- COLSIZE, we can just have j skip over
    //the columns that we already know will equal 0 and focus on the columns
    //that have dependent values.
    if(i <= (COLSIZE + 1))
    {
      j = 0;
      k = i + COLSIZE;
    }
    else if(i >= SIZE - COLSIZE - 1)
    {
      j = i - COLSIZE;
      k = SIZE - 1;
    }
    else
    {
      j = i - COLSIZE;
      k = i + COLSIZE;
    }
    for(; j < k; j++)
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

  //Since we know that 'W' or 0 values in the x vector won't have their weights
  //determined by their neighbors, we go through the A matrix and set any values
  //that depend on a 'W' neighbor to 0.
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

  //This loop decomposes the A matrix into a lower triangular matrix.
  for(i = 0; i < SIZE; ++i)
  {
    //We can use the same properties that we used in the construction of the
    //A matrix to bound the loop through the columns to only focus on the area
    //within the band.
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
      //A similar band check.
      if(i <= (COLSIZE + 1))
      {
        k = 0;
      }
      else
      {
        k = i - (COLSIZE + 1);
      }

      //Based off of the formula for cholesky decomposition, for any points on
      //the diagonal  L(i,i) = the square root of A(i,i) minus the sum of all
      //the points on that row from the L matrix.
      if(i == j)
      {
        for(; k < j; ++k)
        {
          temp += std::pow(L(i,k),2);
        }
        L(i,j) = std::sqrt(A(j,j) - temp);
      }
      //For any point not on the diagonal, L(i,j) = 1/L(j,j) times A(i,j) minus
      //the sum of all the products of L(i,k) * L(j,k).
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

  //Solving the y vector for Ly = b using forward substitution.
  for(i = 0; i < SIZE; ++i)
  {
    //similar bound check.
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

  //solving the x vector for (U)x = y using backward substitution with U =
  //L.transpose().
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

  //resetting k
  k = 0;

  //Filling in the matrix representation of the solution so it can be
  //cleanly returned to main.
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
