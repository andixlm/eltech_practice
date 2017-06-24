#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(int iterations = 1);

    bool setIterations(int iterations);
    int getIterations();

private:
    int mIterations;
};

#endif // KOCHFRACTAL_HPP
