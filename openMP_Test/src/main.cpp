// Created by Sebastian Yde Madsen on 20/05/2022 for testing openMP on MacOS w. M1 pro chip
#include <iostream>
#include <cmath>

// main function
int main()
{

//Specifying the parallel region (creating threads)
#pragma omp parallel
    {
        std::cout << "Hello World" << std::endl;
    }

    const int size = 10;
    double sinTable[size];

// Initializing table in parallel
#pragma omp parallel for
    for(int n=0; n<size; n++)
        sinTable[n] = std::sin(2 * M_PI * n / size);

//Printing table
    for(int i= 0; i<size; i++)
    {
        std::cout << sinTable[i] << std::endl;
    }
    return 0;
}