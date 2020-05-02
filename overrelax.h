/**
 * @file    
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   
 * @brief   Due: 
 * @date    
 *
 * @brief   
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
        /**
        * @brief    
        * @pre      
        * @post     
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
        * @brief    
        * @pre      
        * @post     
        */
        overrelax(const overrelax& source) noexcept
            : m_data(source.m_data)
            , m_step(source.m_step)
            , m_resolved(source.m_resolved)
        {};

        /**
        * @brief    
        * @pre      
        * @post     
        */
        bool resolved() const noexcept;

        /**
        * @brief    
        * @pre      
        * @post     
        */
        bool verify() noexcept;

        /**
        * @brief    
        * @pre      
        * @post     
        */
        overrelax& operator=(const overrelax& source) noexcept;

        /**
        * @brief    
        * @pre      
        * @post     
        */
        overrelax& operator()() noexcept;

        /**
        * @brief    
        * @pre      
        * @post     
        */
        friend std::ostream& operator << (std::ostream& out,
                                          const overrelax& i) noexcept;
};

#endif /* OVERRELAX_H */