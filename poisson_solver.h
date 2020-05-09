/**
 * @file    poisson_solver.h
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 - Complex Numbers, Outer Products, and Quantum Computing
 * @brief   Due: 5/10/2020
 * @date    5/3/2020
 *
 * @brief   
*/

#include "nTrix.h"

#ifndef POISSON_SOLVER_H
#define POISSON_SOLVER_H

/**
 * @class   poisson_solver
 * @brief   
 */
template <typename DerivedSolver>
class poisson_solver
{
    public:
        /**
        * @brief    Used to get the solution to the poisson equation
        * @pre      based on implimentation.
        * @post     returns the solution matrix
        * 
        * @exception    errors are based on implimentation.
        * 
        * @param    data - the input char matrix to be used as a base
        * @param    step - the cost to move to an adjacent cell, must be greater
        *                  than zero
        *
        * @return   the solution matrix
        */
        virtual nTrix<float> operator() (const nTrix<char>& data,
                                                float step) const = 0;

        /**
        * @brief    Used to print out the matrix in a comma deliminated fashion
        * @pre      N/A
        * @post     modifies the passed parameter to print out the comma
        *           deliminated matrix
        *
        * @param    out - the ostream that takes in the output
        */
        virtual void print(std::ostream& out, const nTrix<float>& data) const
                                                                   noexcept = 0;
};

#endif /* POISSON_SOLVER_H */