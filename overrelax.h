/**
 * @file    overrelax.h
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/2/20
 *
 * @brief   This is a solution definition to the possion equation. This is an
 *          implimentaiton of the over-relax algorithm.
*/

#include "nTrix.h"
#include "poisson_solver.h"

#ifndef OVERRELRX_H
#define OVERRELAX_H

/**
 * @class   
 * @brief   
 */
class overrelax : public poisson_solver<overrelax>
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
        void lenInvalArg(const std::string& msg) const;
    public:

        /********************* output functions *********************/
        /**
        * @brief    Checks to see if the solution is solved. Used to double
        *           check the values
        * @pre      N/A
        * @post     returns if the state has been verified to have been solved
        *           with sufficient accuracy
        * 
        * @param    data - the matrix to be verified.
        * @param    step - the cost to move to an adjacent cell, must be greater
        *                  than zero
        * 
        * @return   if the state has been verified to have been solved with
        *           sufficient accuracy
        */
        bool verify(const nTrix<float>& data, float step) noexcept;

        /**
        * @brief    Used to get the solution to the poisson equation
        * @pre      the matrix must be at least a 1x1, and the step size must be
        *           greater than 0
        * @post     returns the solution matrix
        * 
        * @exception    throws a invalid argument error if the matrix is too
        *               small or the step size is less than 1.
        * 
        * @param    data - the input char matrix to be used as a base
        * @param    step - the cost to move to an adjacent cell, must be greater
        *                  than zero
        *
        * @return   the solution matrix
        */
        nTrix<float> operator()(const nTrix<char>& data, float step) const;
};

#endif /* OVERRELAX_H */