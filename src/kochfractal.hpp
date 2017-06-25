#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include <QLineF>

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(QLineF fLine, QLineF sLine, QLineF tLine);

    bool setIterations(int iterations);
    int getIterations() const;

private:
    const int DEFAULT_ITERATIONS = 1;

    int mIterations;

    KochTree mKochTree;

    void processFractal();
};

#endif // KOCHFRACTAL_HPP
