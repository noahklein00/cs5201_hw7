#include "cholesky.h"
#include "nTrix.h"
#include "vector.h"
#include "symMat.h"
#include <iostream>
#include <fstream>

int main()
{
  int start_s;
  int stop_s;
  start_s = clock();
  const int SIZE = 6084;
  std::ifstream fin;
  fin.open("output.txt");
  std::ofstream fout;
  fout.open("heatmap.csv");
  char a;
  cholesky tester;

  vector<float> tempVec(SIZE);
  vector<float> sysX(SIZE);
  vector<float> sysB(SIZE);
  nTrix<float> A(SIZE,SIZE);
  int counter = 0;
  int counter2 = 0;
  float temp = 0;
  int rowCount = 0;
  int colCount = 0;

  while(fin)
  {
    fin.get(a);
    if(rowCount == 0)
    {
      colCount++;
    }
    if(a == 'W')
    {
      tempVec[counter] = 0;
      ++counter;
    }
    else if(a == 'B')
    {
      tempVec[counter] = 1;
      ++counter;
    }
    else if(a == '\n')
    {
      rowCount++;
    }
  }
  rowCount -= 1;
  colCount -= 1;
  counter = 0;

  for(int i = rowCount-1; i >= 0; --i)
  {
    for(int j = 0; j < colCount; ++j)
    {
      sysX[counter] = tempVec[i*colCount + j];
      ++counter;
    }
  }

  for(int i = 0; i < SIZE; ++i)
  {
    sysB[i] = 1;
  }

  for(int i = 0; i < A.rows(); i++)
  {
    for(int j = 0; j < A.rows(); j++)
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

  counter = 0;

  for(int i = 0; i < sysX.size(); ++i)
  {
    if(sysX[i] == 0)
    {
      for(int j = 0; j < sysX.size(); ++j)
      {
        if(i != j)
        {
          A(i,j) = 0;
        }
        if(j > i)
        {
          A(j,i) = 0;
        }
      }
    }
  }

  for(int i = 0; i < sysX.size(); i++)
  {
    if(sysX[i] == 0)
    {
      sysB[i] = 0;
    }
  }

  //std::cout << A << std::endl;

  sysX = tester(A,sysX, sysB);

  for(int i = rowCount-1; i >= 0; --i)
  {
    for(int j = 0; j < colCount; ++j)
    {
      if(j != 0)
      {
        fout << "," << sysX[i*colCount + j];
      }
      else
      {
        fout << sysX[i*colCount + j];
      }
    }
    fout << std::endl;
  }

  fin.close();
  fout.close();

  stop_s = clock();
  std::cout << "Finish: " << (stop_s - start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

  return 0;
}
