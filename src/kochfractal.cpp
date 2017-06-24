#include "kochfractal.hpp"

KochFractal::KochFractal(int iterations)
    : mIterations(iterations)
{

}

bool KochFractal::setIterations(int iterations)
{
    if (iterations < 1)
    {
        return false;
    }

    mIterations = iterations;

    return true;
}

int KochFractal::getIterations() const
{
    return mIterations;
}
