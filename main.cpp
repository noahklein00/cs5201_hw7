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
#include "overrelax.h"

/** cost to move from one pixel to the next */
const float STEPSIZE = 1;

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
        std::filebuf inputFile;
        inputFile.open(argv[1], std::iostream::in);
        std::istream inputData(&inputFile);

        nTrix<char> inputMat(0, 0);

        inputData >> inputMat;

        overrelax relax(inputMat, STEPSIZE);

        while (!relax.resolved())
        {
            relax();
        }

        std::ofstream outputFile (argv[2], std::ofstream::out);

        outputFile << relax << std::endl;

        outputFile.close();
    }

    
    return 0;
}