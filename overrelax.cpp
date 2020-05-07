/**
 * @file    overrelax.cpp
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/2/20
*/

#include "overrelax.h"

/********************* other functions *********************/
void overrelax::lenInvalArg(const std::string& msg) const
{
    std::cout << msg << std::endl;
    throw std::invalid_argument(msg);
}

/********************* output functions *********************/
bool overrelax::verify(const nTrix<float>& data, float step) noexcept
{
    bool resolved = true;

    for (short row = 1; row < data.rows() - 1; row++)
    {
        for (short col = 1; col < data.cols() - 1; col++)
        {
            if (data(row, col) != 0)
            {
                const float val = (data(row - 1, col) + data(row + 1, col) +
                                data(row, col - 1) + data(row, col + 1))/4 +
                                step;
                if (data(row, col) > val + m_error ||
                    data(row, col) < val - m_error)
                {
                    resolved = false;
                }
            }
        }
    }

    return resolved;
}

nTrix<float> overrelax::operator()(const nTrix<char>& data, float step) const
{
    if (step < 0)
    {
        const std::string err = "Step size must be greater than 1. "
                                "Passed step size: " + 
                                std::to_string(step);
        lenInvalArg(err);
    }
    if (data.rows() < 1)
    {
        const std::string err = "the number of rows in the input data "
                                "must bre greater than 1. Passed number"
                                " of rows: " +
                                std::to_string(data.rows());
        lenInvalArg(err);
    }
    if (data.cols() < 1)
    {
        const std::string err = "the number of cols in the input data "
                                "must bre greater than 1. Passed number"
                                " of cols: " +
                                std::to_string(data.cols());
        lenInvalArg(err);
    }

    nTrix<float> result(data.rows() + 2, data.cols() + 2);
    for (short row = 0; row < result.rows(); row++)
    {
        for (short col = 0; col < result.cols(); col++)
        {
            if (row == 0 || col == 0 || row == result.rows() - 1 ||
                col == result.cols() - 1)
            {
                result(row, col) = 0;
            }
            else
            {
                result(row, col) = data(row - 1, col - 1) == 'W'
                                    ? 0 : 1;
            }
        }
    }

    bool resolved = false;

    while (!resolved)
    {
        resolved = true;

        short skip = 0;

        for (short row = 1; row < result.rows() - 1; row++)
        {
            for (short col = 1 + skip; col < result.cols() - 1; col++)
            {
                if (result(row, col) != 0)
                {
                    const float val = (result(row - 1, col) +
                                      result(row + 1, col) +
                                      result(row, col - 1) +
                                      result(row, col + 1))/4 + step;
                    if (result(row, col) > val + m_error ||
                        result(row, col) < val - m_error)
                    {
                        resolved = false;
                    }
                    result(row, col) = val;
                }
            }

            skip = skip == 0 ? 1 : 0;
        }
        
        skip = 1;

        for (short row = 1; row < result.rows() - 1; row++)
        {
            for (short col = 1; col < result.cols() - 1; col++)
            {
                if (result(row, col) != 0)
                {
                    const float val = (result(row - 1, col) +
                                      result(row + 1, col) +
                                      result(row, col - 1) +
                                      result(row, col + 1))/4 + step;
                    result(row, col) = val;
                }
            }

            skip = skip == 0 ? 1 : 0;
        }
    }

    return result;
}