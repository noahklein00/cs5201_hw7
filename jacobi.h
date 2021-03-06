/**
 * @file    jacobi.h
 * @author  Jeffrey Strahm and Noah Klein
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/10/20
 *
 * @brief   This is a solution definition to the possion equation. This is an
 *          implimentaiton of the over-relax algorithm.
*/

#include "nTrix.h"
#include "poisson_solver.h"

#ifndef OVERRELRX_H
#define jacobi_H

/**
 * @class jacobi
 * @brief This is a solution definition to the possion equation. This is an
 *          implimentaiton of the over-relax algorithm.
 */
class jacobi : public poisson_solver<jacobi>
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
        * @brief    creates a jacobi class
        * @pre      N/A
        * @post     creates a jacobi class with an error of .000001. This is
        *           the maximum absolute change between iterations that is
        *           accepted for a found solution per cell
        */
        jacobi() noexcept
            : m_error(.000001)
        {};

        /**
        * @brief    creates a jacobi class
        * @pre      N/A
        * @post     creates a jacobi class with the passed error
        *
        * @param    error - the maximum absolute change between iterations that
        *                   is accepted for a found solution per cell
        */
        jacobi(const float error)
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
        * @brief    jacobi copy constructor
        * @pre      N/A
        * @post     creates a jacobi class with the same error
        *
        * @param    source - the jacobi class to copy
        */
        jacobi(const jacobi& source) noexcept
            : m_error(source.m_error)
        {};

        /********************* operator functions *********************/
        /**
        * @brief    jacobi copy constructor
        * @pre      N/A
        * @post     creates a jacobi class with the same error
        *
        * @param    source - the jacobi class to copy
        */
        jacobi& operator= (const jacobi& source) noexcept;

        /**
        * @brief    Used to get the solution to the poisson equation
        * @pre      the matrix must be at least a 1x1, and the step size must be
        *           greater than 0
        * @post     returns the solution matrix with number within the error
        *           threshold. The solution matrix has a padding of 0's around
        *           it
        *
        * @exception    throws a invalid argument error if the matrix is too
        *               small or the step size is less than 1.
        *
        * @param    data - the input char matrix to be used as a base
        * @param    step - the cost to move to an adjacent cell, must be greater
        *                  than zero
        *
        * @return   the solution matrix with an extra padding of 0's around it
        */
        nTrix<float> operator()(const nTrix<char>& data, const float step) const
                                                                       override;

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
        bool verify(const nTrix<float>& data, const float step) noexcept;

        /**
        * @brief    Used to print out the matrix in a comma deliminated fashion
        * @pre      N/A
        * @post     modifies the passed parameter to print out the comma
        *           deliminated matrix. The print out goes to 6 significant
        *           figures. Does not print out the first and last rows and
        *           columns
        *
        * @param    out - the ostream that takes in the output
        * @param    data - nTrix<float> that is filled with the solution to the
        *           given system.
        */
        void print(std::ostream& out, const nTrix<float>& data) const noexcept
                                                                       override;
};

#endif /* jacobi_H */
