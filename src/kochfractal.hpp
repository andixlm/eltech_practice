#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(int iterations = DEFAULT_ITERATIONS);

    bool setIterations(int iterations);
    int getIterations();

private:
    const int DEFAULT_ITERATIONS = 1;

    int mIterations;
};

#endif // KOCHFRACTAL_HPP
