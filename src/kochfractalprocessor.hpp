#ifndef KOCHFRACTALPROCESSOR_HPP
#define KOCHFRACTALPROCESSOR_HPP

#include <QObject>

#include "kochfractal.hpp"

class KochFractalProcessor : public QObject
{
    Q_OBJECT

public:
    KochFractalProcessor(KochFractal* kochFractal);

public slots:
    void process();

private:
    KochFractal* mKochFractal;

signals:
    void finished();
};

#endif // KOCHFRACTALPROCESSOR_HPP
