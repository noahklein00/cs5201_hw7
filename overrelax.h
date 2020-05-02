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

#ifndef OVERRELRX_H
#define OVERRELAX_H

/**
 * @class   
 * @brief   
 */
class overrelax
{
    private:
        nTrix<float> m_data;
        float m_step;
        bool m_resolved;
        /********************* other functions *********************/
        /**
        * @brief    prints out and throws a length error
        * @pre      N/A
        * @post     ends the program
        *
        * @exception    throws a length error.
        *
        * @param    msg - the message printed to explain the error
        */
        void lenError(const std::string& msg) const;
    public:
        /********************* constructors *********************/
        /**
        * @brief    creates an instance of the overrelax algorithm. If non 'B'
        *           and 'W' chars are entered, they will be treated as 'B'.
        * @pre      step size ust be greater than 0, and the matrix must be at
        *           least a 1x1. data must contain 'B' and 'W' chars only.
        * @post     creates an instance of the overrelax algorithm
        * 
        * @param    data - the char matrix of the image to be examined.
        * @param    step - the minimum cost to move from one pixel to another.
        * 
        * @exception    throws a length error if the step size is less than zero
        *               or the matrix is less than 1x1
        */
        overrelax(nTrix<char> data, float step)
            : m_data(data.rows() + 2, data.cols() + 2)
            , m_step(step)
            , m_resolved(false)
        {
            if (step < 0)
            {
                const std::string err = "Step size must be greater than 1. "
                                        "Passed step size: " + 
                                        std::to_string(step);
                lenError(err);
            }
            if (data.rows() < 1)
            {
                const std::string err = "the number of rows in the input data "
                                        "must bre greater than 1. Passed number"
                                        " of rows: " +
                                        std::to_string(data.rows());
                lenError(err);
            }
            if (data.cols() < 1)
            {
                const std::string err = "the number of cols in the input data "
                                        "must bre greater than 1. Passed number"
                                        " of cols: " +
                                        std::to_string(data.cols());
                lenError(err);
            }
            for (short row = 0; row < m_data.rows(); row++)
            {
                for (short col = 0; col < m_data.cols(); col++)
                {
                    if (row == 0 || col == 0 || row == m_data.rows() - 1 ||
                        col == m_data.cols() - 1)
                    {
                        m_data(row, col) = 0;
                    }
                    else
                    {
                        m_data(row, col) = data(row - 1, col - 1) == 'W'
                                           ? 0 : 1;
                    }
                }
            }
        };

        /**
        * @brief    copies an instance of overrelax
        * @pre      N/A
        * @post     makes a new instance of overrelax the same as the passed
        *           instance.
        * 
        * @param    source - the overrelax instance to be copied
        */
        overrelax(const overrelax& source) noexcept
            : m_data(source.m_data)
            , m_step(source.m_step)
            , m_resolved(source.m_resolved)
        {};

        /********************* status functions *********************/
        /**
        * @brief    returns whither or not the solution has been found to
        *           sufficient accuracy.
        * @pre      N/A
        * @post     returns if the problem is solved with sufficient accuracy.
        * 
        * @return   if the problem is solved with sufficient accuracy.
        */
        bool resolved() const noexcept;

        /**
        * @brief    Checks to see if the solution is solved. Used to double
        *           check the values
        * @pre      N/A
        * @post     returns if the state has been verified to have been solved
        *           with sufficient accuracy
        * 
        * @return   if the state has been verified to have been solved with
        *           sufficient accuracy
        */
        bool verify() noexcept;

        /********************* operator functions *********************/
        /**
        * @brief    copy by assignment operator
        * @pre      N/A
        * @post     makes the current instance of overrelax the same as the
        *           passed instance.
        * 
        * @param    source - the overrelax instance to be copied
        * 
        * @return   a reference to the current instance of overrelax
        */
        overrelax& operator=(const overrelax& source) noexcept;

        /**
        * @brief    Does corrective calculations on the value of all U values
        * @pre      N/A
        * @post     corrects the data a bit and marks it as resolved if the
        *           changes fall within acceptable error
        * 
        * @return a reference to the current instance of overrelax
        */
        overrelax& operator()() noexcept;

        /**
        * @brief    used to print out the data of the list to a ostream
        * @pre      Type T must support the << operator
        * @post     print out the data in a comma deliminated fashion
        *
        * @param    out - the ostream that takes in the output
        * @param    i - the overrelax instance the data will be print from
        *
        * @return   a reference to the ostream
        */
        friend std::ostream& operator << (std::ostream& out,
                                          const overrelax& i) noexcept;
};

#endif /* OVERRELAX_H */