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
  const int ROOTSIZE = sqrt(L.rows());

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

  //filling the A matrix with values
  // for(i = 0; i < A.rows(); ++i)
  // {
  //   // if(x[i] != 0)
  //   // {
  //   if(i <= ROOTSIZE + 1)
  //   {
  //     j = 0;
  //   }
  //   else
  //   {
  //     j = i - (ROOTSIZE + 1);
  //   }
  //   if(i < SIZE - ROOTSIZE - 1)
  //   {
  //     k = i + ROOTSIZE;
  //   }
  //   else
  //   {
  //     k = A.rows();
  //   }
  //     for(; j < k; ++j)
  //     {
  //       std::cout << "j: " << j << std::endl;
  //       if(i == j)
  //       {
  //         A(i,j) = 1.0;
  //       }
  //       else if(i == j-1 && ((i+1)%static_cast<int>(sqrt(A.rows()))) != 0)
  //       {
  //         A(i,j) = -.25;
  //       }
  //       else if(i == j+1 && ((i)%static_cast<int>(sqrt(A.rows()))) != 0)
  //       {
  //         A(i,j) = -.25;
  //       }
  //       else if(i == j-sqrt(A.rows()))
  //       {
  //         A(i,j) = -.25;
  //       }
  //       else if(i == j+sqrt(A.rows()))
  //       {
  //         A(i,j) = -.25;
  //       }
  //       else
  //       {
  //         A(i,j) = 0.0;
  //       }
  //     }
  //   // }
  //   // else
  //   // {
  //   //   A(i,i) = 1.0;
  //   // }
  // }
  //
  // for(i = 0; i < A.rows(); ++i)
  // {
  //   if(x[i] == 0)
  //   {
  //     for(j = 0; j < A.rows(); ++j)
  //     {
  //       if(i != j)
  //       {
  //         A(i,j) = 0;
  //         A(j,i) = 0;
  //       }
  //     }
  //   }
  // }

  for(i = 0; i < A.rows(); i++)
  {
    for(j = 0; j < A.rows(); j++)
    {
      if(i == j)
      {
        A(i,j) = 1.0;
      }
      else if(i == j-1 && ((i+1)%static_cast<int>(sqrt(A.rows()))) != 0)
      {
        A(i,j) = -.25;
      }
      else if(i == j+1 && ((i)%static_cast<int>(sqrt(A.rows()))) != 0)
      {
        A(i,j) = -.25;
      }
      else if(i == j-sqrt(A.rows()))
      {
        A(i,j) = -.25;
      }
      else if(i == j+sqrt(A.rows()))
      {
        A(i,j) = -.25;
      }
      else
      {
        A(i,j) = 0.0;
      }
    }
  }

  for(i = 0; i < static_cast<int>(x.size()); ++i)
  {
    if(x[i] == 0)
    {
      for(j = 0; j < static_cast<int>(x.size()); ++j)
      {
        if(i != j)
        {
          A(i,j) = 0;
          A(j,i) = 0;
        }
        // if(j > i)
        // {
        //   A(j,i) = 0;
        // }
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
    if(i <= (ROOTSIZE + 1))
    {
      j = 0;
    }
    else
    {
      j = i - (ROOTSIZE + 1);
    }

    for(; j <= i; ++j)
    {
      if(i <= (ROOTSIZE + 1))
      {
        k = 0;
      }
      else
      {
        k = i - (ROOTSIZE + 1);
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

  for(i = 0; i < static_cast<int>(y.size()); ++i)
  {
    if(x[i] != 0)
    {
      // if(i <= ROOTSIZE + 1)
      // {
      //   j = 0;
      // }
      // else
      // {
      //   j = i - (ROOTSIZE + 1);
      // }
      for(j = 0; j < i; ++j)
      {
        temp += L(i,j) * y[j];
      }
      y[i] = (b[i] - temp)/L(i,i);
      temp = 0;
    }
  }

  for(i = x.size()-1; i >= 0; --i)
  {
    if(x[i] != 0)
    {
      // if(i >= SIZE - ROOTSIZE - 1)
      // {
      //   j = 0;
      // }
      // else
      // {
      //   j = i + ROOTSIZE;
      // }
      for(j = x.size()-1; j > i; --j)
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

// void cholesky::print(std::ostream& out) const noexcept
// {
//   out << (*this);
//   return;
// }
//
// std::ostream& operator<<(std::ostream& out,const cholesky& i) noexcept
// {
//   int y = 0;
//   for(int x = 0; x < i.solution.rows(); ++x)
// 	{
// 		for(y = 0; y < i.solution.cols(); ++y)
// 		{
//       if(y != 0)
//       {
//         out << "," << i.solution(x,y);
//       }
//       else
//       {
//         out << i.solution(x,y);
//       }
// 		}
//     out << std::endl;
// 	}
//
//   return out;
// }

// vector<float> cholesky::operator()(const nTrix<float>& A, vector<float>& x, const vector<float>& b)
// {
//   nTrix<float> L(A.rows(), A.cols());
//   //nTrix<float> U(A.rows(), A.cols());
//   vector<float> y(A.rows());
//   float temp = 0;
//
//   for(int i = 0; i < L.rows(); i++)
//   {
//     for(int j = 0; j < L.cols(); j++)
//     {
//       L(i,j) = float(0.0);
//       //U(i,j) = float(0.0);
//     }
//   }
//
//   int s = 0;
//   int t = 0;
//   int r = 0;
//   //start_s = clock();
//   for(; s < L.rows(); ++s)
//   {
//     if(s <= sqrt(L.rows())+1)
//     {
//       t=0;
//     }
//     else
//     {
//       t = s - (sqrt(L.rows())+1);
//     }
//     //t = 0;
//     for(; t <= s; ++t)
//     {
//       //r = 0;
//       if(s <= sqrt(L.rows())+1)
//       {
//         r=0;
//       }
//       else
//       {
//         r = s - (sqrt(L.rows())+1);
//       }
//       if(s == t)
//       {
//         for(; r < t; ++r)
//         {
//           temp += std::pow(L(s,r),2);
//         }
//         L(s,t) = std::sqrt(A(t,t) - temp);
//       }
//       else
//       {
//         for(; r < t; ++r)
//         {
//           temp += (L(s,r) * L(t,r));
//         }
//         L(s,t) = (1.0/L(t,t)) * (A(s,t) - temp);
//       }
//       temp = 0;
//     }
//   }
//
//   //U = L.transpose();
//   for(int i = 0; i < y.size(); i++)
//   {
//     if(x[i] != 0) //skips solving the white pixels
//     {
//       for(int j = 0; j < i; j++)
//       {
//         temp += L(i,j) * y[j];
//       }
//       y[i] = (b[i] - temp)/L(i,i);
//       temp = 0;
//     }
//   }
//
//   for(int i = x.size()-1; i >= 0; i--)
//   {
//     if(x[i] != 0) //skips solving the white pixels
//     {
//       for(int j = x.size()-1; j > i; j--)
//       {
//         temp += L(j,i) * x[j];
//       }
//       x[i] = (y[i] - temp)/L(i,i);
//       temp = 0;
//     }
//   }
//   return x;
// }


void cholesky::print(std::ostream& out, const nTrix<float>& data) const noexcept
{
	for(int x = 0; x < data.rows(); x++)
	{
		for(int y = 0; y < data.cols(); y++)
		{
			out << data(x, y) << ",";
		}
		if(x < data.rows() - 2)
		{
			out << std::endl;
		}
	}
}