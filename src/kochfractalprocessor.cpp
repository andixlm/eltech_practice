#include "kochfractalprocessor.hpp"

KochFractalProcessor::KochFractalProcessor(KochFractal* kochFractal)
    : mKochFractal(kochFractal)
{

}

void KochFractalProcessor::process()
{
    mKochFractal->process();

    emit finished();
}
