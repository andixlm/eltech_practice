#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(int iterations = MINIMUM_ITERATIONS);

    bool setIterations(int iterations);
    int getIterations();

private:
    const int MINIMUM_ITERATIONS = 1;

    int mIterations;
};

#endif // KOCHFRACTAL_HPP
