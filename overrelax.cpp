/**
 * @file    overrelax.cpp
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 5/10/20
 * @date    5/2/20
*/

#include "overrelax.h"

const float RELAXERROR = 0.000001;

/********************* other functions *********************/
void overrelax::lenError(const std::string& msg) const
{
    std::cout << msg << std::endl;
    throw std::length_error(msg);
}

/********************* status functions *********************/
bool overrelax::resolved() const noexcept
{
    return m_resolved;
}

bool overrelax::verify() noexcept
{
    m_resolved = true;

    for (short row = 1; row < m_data.rows() - 1; row++)
    {
        for (short col = 1; col < m_data.cols() - 1; col++)
        {
            if (m_data(row, col) != 0)
            {
                const float val = (m_data(row - 1, col) + m_data(row + 1, col) +
                                m_data(row, col - 1) + m_data(row, col + 1))/4 +
                                m_step;
                if (m_data(row, col) > val + RELAXERROR ||
                    m_data(row, col) < val - RELAXERROR)
                {
                    m_resolved = false;
                }
            }
        }
    }

    return m_resolved;
}

/********************* operator functions *********************/
overrelax& overrelax::operator=(const overrelax& source) noexcept
{
    if (this == &source)
    {
        return *this;
    }

    m_data = source.m_data;
    m_step = source.m_step;
    m_resolved = source.m_resolved;

    return *this;
}

overrelax& overrelax::operator()() noexcept
{
    m_resolved = true;

    short skip = 0;

    for (short row = 1; row < m_data.rows() - 1; row++)
    {
        for (short col = 1 + skip; col < m_data.cols() - 1; col++)
        {
            if (m_data(row, col) != 0)
            {
                const float val = (m_data(row - 1, col) + m_data(row + 1, col) +
                                m_data(row, col - 1) + m_data(row, col + 1))/4 +
                                m_step;
                if (m_data(row, col) > val + RELAXERROR ||
                    m_data(row, col) < val - RELAXERROR)
                {
                    m_resolved = false;
                }
                m_data(row, col) = val;
            }
        }

        skip = skip == 0 ? 1 : 0;
    }
    
    skip = 1;

    for (short row = 1; row < m_data.rows() - 1; row++)
    {
        for (short col = 1; col < m_data.cols() - 1; col++)
        {
            if (m_data(row, col) != 0)
            {
                const float val = (m_data(row - 1, col) + m_data(row + 1, col) +
                                m_data(row, col - 1) + m_data(row, col + 1))/4 +
                                m_step;
                m_data(row, col) = val;
            }
        }

        skip = skip == 0 ? 1 : 0;
    }
    return *this;
}

std::ostream& operator << (std::ostream& out, const overrelax& i) noexcept
{
	for(int x = 1; x < i.m_data.rows() - 1; x++)
	{
		for(int y = 1; y < i.m_data.cols() - 1; y++)
		{
			out << i.m_data(x, y) << ",";
		}
		if(x < i.m_data.rows() - 2)
		{
			out << std::endl;
		}
	}

    return out;
}