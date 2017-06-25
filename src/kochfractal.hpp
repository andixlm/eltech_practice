#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(int iterations = 1);

    bool setIterations(int iterations);
    int getIterations() const;

private:
    int mIterations;

    KochTree mKochTree;
};

#endif // KOCHFRACTAL_HPP
