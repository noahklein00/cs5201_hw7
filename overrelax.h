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
        /** The minimal change needed to mark the solution as found (+/-)*/
        float m_error;
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
        /********************* constructor/destructors *********************/
        /**
        * @brief    creates a overrelax class 
        * @pre      N/A
        * @post     creates a overrelax class with an error of .000001. This is
        *           the maximum absolute change between iterations that is
        *           accepted for a found solution per cell
        */
        overrelax() noexcept
            : m_error(.000001)
        {};

        /**
        * @brief    creates a overrelax class 
        * @pre      N/A
        * @post     creates a overrelax class with the passed error
        * 
        * @param    error - the maximum absolute change between iterations that
        *                   is accepted for a found solution per cell
        */
        overrelax(float error)
            : m_error(error)
        {
            if (error <= 0)
            {
                const std::string err = "error mussed be greater than 0. Passed"
                                        " error: " + std::to_string(error);
                invalArgErr(err);
            }
        };

        /**
        * @brief    overrelax copy constructor
        * @pre      N/A
        * @post     creates a overrelax class with the same error
        * 
        * @param    source - the overrelax class to copy
        */
        overrelax(const overrelax& source) noexcept
            : m_error(source.m_error)
        {};

        /********************* operator functions *********************/
        /**
        * @brief    overrelax copy constructor
        * @pre      N/A
        * @post     creates a overrelax class with the same error
        * 
        * @param    source - the overrelax class to copy
        */
        overrelax& operator= (const overrelax& source) noexcept;

        /**
        * @brief    Used to get the solution to the poisson equation
        * @pre      the matrix must be at least a 1x1, and the step size must be
        *           greater than 0
        * @post     returns the solution matrix with number within the error
        *           threshold
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
        * @brief    Used to print out the matrix in a comma deliminated fashion
        * @pre      N/A
        * @post     modifies the passed parameter to print out the comma
        *           deliminated matrix. The print out goes to 6 significant
        *           digits
        *
        * @param    out - the ostream that takes in the output
        */
        void print(std::ostream& out, const nTrix<float>& data) const noexcept;
};

#endif /* OVERRELAX_H */