/**
 * @file    cholesky.h
 * @author  Jeffrey Strahm and Noah Klein
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/2/20
 *
 * @brief   This class solves the poisson equation using an improved method
 *          of LU decomposition know as cholesky decompostion. This takes
 *          advantage of the fact that the creation of the A matrix in the
 *          system will be symmetric and weakly positive definite.
*/

#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "nTrix.h"
#include "poisson_solver.h"
#include <cmath>
#include <ctime>

/**
 * @class cholesky
 * @brief This class solves the poisson equation using an improved method
 *          of LU decomposition know as cholesky decompostion. This takes
 *          advantage of the fact that the creation of the A matrix in the
 *          system will be symmetric and weakly positive definite.
 */
class cholesky: public poisson_solver<cholesky>
{
  private:

    /********************* other functions *********************/
    /**
    * @brief    prints out and throws a invalid_argument error
    * @pre      N/A
    * @post     ends the program
    *
    * @exception    throws a invalid_argument error.
    *
    * @param    msg - the message printed to explain the error
    */
    void invalArgErr(const std::string& msg) const;
  public:

    /**
    * @brief    operator () overload for the cholesky class that takes an input
    *           matrix of char's and a step size that represents the forcing
    *           function to solve the system using cholesky decomposition.
    * @pre      The input matrix must be only B and W. The step size must be
    *           greater than 0.
    * @param    data - The character matrix that represents the boundary of the
    *           image.
    * @param    step - The step size that determines the forcing function.
    * @return   Returns a nTrix<float> object that stores the values of the
    *           unique solution to the system.
    * @throws   Throws a invalArgErr if the step parameter is not greater than
    *           zero or if the data parameter is not made up of only B and W.
    */
    virtual nTrix<float> operator()(const nTrix<char>& data, float const step)
      const override;

    /**
    * @brief    Used to print out the matrix in a comma deliminated fashion
    * @pre      N/A
    * @post     modifies the passed parameter to print out the comma
    *           deliminated matrix. The print out goes to 6 significant
    *           digits
    *
    * @param    out - the ostream that takes in the output
    * @param    data - nTrix<float> that is filled with the solution to the
    *           given system.
    */
    void print(std::ostream& out, const nTrix<float>& data) const noexcept override;
};

#endif
