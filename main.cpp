/**
 * @file    main.cpp
 * @author  Jeffrey Strahm
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 6 - Complex Numbers, Outer Products, and Quantum Computing
 * @brief   Due: 4/20/2020
 * @date    4/20/2020
 * 
 * @brief   This is the driver that runs the lander situation using a
 *          combination of filters.
*/

#include <numeric>
#include "nTrix.h"

/**
 * @brief       driver to run the models for landing a spaceship on the moon
 * 
 * @exception   The exceptions ofo it's called functions. Currently domain and
 *              length
 * 
 * @returns     0
 */
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        throw(std::invalid_argument(std::to_string(argc)));
    }

    const int func = std::stoi(argv[3]);

    if (func < 0 || func > 1)
    {
        throw(std::invalid_argument(std::to_string(func)));
    }

    if (func == 0)
    {

    }
    else
    {
        
    }
    
    return 0;
}