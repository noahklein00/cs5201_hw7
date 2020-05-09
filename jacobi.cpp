/**
 * @file    jacobi.cpp
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/2/20
*/

#include "jacobi.h"

/********************* other functions *********************/
void jacobi::invalArgErr(const std::string& msg) const
{
    std::cout << msg << std::endl;
    throw std::invalid_argument(msg);
}

/********************* operator functions *********************/
jacobi& jacobi::operator= (const jacobi& source) noexcept
{
    m_error = source.m_error;

    return *this;
}

nTrix<float> jacobi::operator()(const nTrix<char>& data, float step) const
{
    if (step < 0)
    {
        const std::string err = "Step size must be greater than 1. "
                                "Passed step size: " + 
                                std::to_string(step);
        invalArgErr(err);
    }
    if (data.rows() < 1)
    {
        const std::string err = "the number of rows in the input data "
                                "must bre greater than 1. Passed number"
                                " of rows: " +
                                std::to_string(data.rows());
        invalArgErr(err);
    }
    if (data.cols() < 1)
    {
        const std::string err = "the number of cols in the input data "
                                "must bre greater than 1. Passed number"
                                " of cols: " +
                                std::to_string(data.cols());
        invalArgErr(err);
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

    const short rowSize = result.rows() - 1;
    const short colSize = result.cols() - 1;

    while (!resolved)
    {
        resolved = true;

        for (short row = 1; row < rowSize; row++)
        {
            for (short col = 1; col < colSize; col++)
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
        }
    }

    return result;
}

/********************* output functions *********************/
bool jacobi::verify(const nTrix<float>& data, float step) noexcept
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

void jacobi::print(std::ostream& out, const nTrix<float>& data) const
                                                                        noexcept
{
	for(int x = 1; x < data.rows() - 1; x++)
	{
		for(int y = 1; y < data.cols() - 1; y++)
		{
			out << data(x, y) << ",";
		}
		if(x < data.rows() - 2)
		{
			out << std::endl;
		}
	}
}