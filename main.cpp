/**
 * @file    main.cpp
 * @author  Jeffrey Strahm and Noah Klein
 * @brief   class: CS5201 - Prof. Price
 * @brief   Homework 7 (Final Project) - Image Analysis with Poisson's Equation
 * @brief   Due: 4/20/2020
 * @date    4/20/2020
 *
 * @brief   This driver takes an input matrix of B and W characters and solves
 *          the poisson equation using a user specified method.
*/

#include <numeric>
#include "nTrix.h"
#include "jacobi.h"
#include "cholesky.h"

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

    std::filebuf inputFile;
    inputFile.open(argv[1], std::iostream::in);
    std::istream inputData(&inputFile);

    nTrix<char> inputMat(0, 0);

    inputData >> inputMat;

    std::ofstream outputFile (argv[2], std::ofstream::out);

    if (func == 0)
    {
        cholesky choly;
        nTrix<float> result = choly(inputMat, STEPSIZE);
        choly.print(outputFile, result);
    }
    else
    {
        jacobi relax;

        nTrix<float> result = relax(inputMat, STEPSIZE);

        relax.print(outputFile, result);
    }

    outputFile.close();

    return 0;
}
