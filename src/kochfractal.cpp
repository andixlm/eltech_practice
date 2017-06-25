#include <QLineF>
#include <QList>
#include <QtMath>

#include "kochfractal.hpp"

KochFractal::KochFractal(int iterations)
    : mIterations(iterations),
      mKochTree(QLineF(), QLineF(), QLineF()) // Set empty for now.
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

void KochFractal::processFractal()
{
    QList<QLineF*> lines;
    QList<QLineF*> newLines, obsltLines;

    // Initialize lines.
    QList<KochNode*> rootChildren = mKochTree.getRoot()->getChildren();
    for (auto node = rootChildren.cbegin(), listEnd = rootChildren.cend();
         node != listEnd; ++node)
    {
        lines.append(new QLineF((*node)->getLine()));
    }

    for (int iterations = this->getIterations(); iterations > 0; --iterations)
    {
        for (auto line = lines.cbegin(), listEnd = lines.cend();
             line != listEnd; ++line)
        {
            double crntX = (*line)->x1();
            double crntY = (*line)->y1();
            double crntLength = (*line)->length();
            double crntAngle = (*line)->angle();
            double crntAngleRadians = qDegreesToRadians(crntAngle);
            double crntCos = qCos(crntAngleRadians);
            double crntSin = qSin(crntAngleRadians);

            /* Lines placed like:
             *
             *              /\
             *             o  t
             *            w    hr
             *           t      ee
             *          /        \
             * -- one --          -- four --
             *
             */

            QLineF* lineOne = new QLineF();
            lineOne->setP1(QPointF(crntX, crntY));
            lineOne->setLength(crntLength / 3.0);
            lineOne->setAngle(crntAngle);

            QLineF* lineTwo = new QLineF();
            lineTwo->setP1(QPointF(crntX + crntLength / 3.0 * crntCos,
                                   crntY + crntLength / 3.0 * crntSin));
            lineTwo->setLength(crntLength / 3.0);
            lineTwo->setAngle(crntAngle - 300.0);

            QLineF* lineThree = new QLineF();
            lineThree->setP1(QPoint(crntX + crntLength / 1.5 * crntCos,
                                    crntY + crntLength / 1.5 * crntSin));
            lineThree->setLength(crntLength / 3.0);
            lineThree->setAngle(crntAngle - 240.0);
            /* Fix third line direction.
             * Its start should be at the end of second line.
             */
            lineThree->setP1(QPointF(
                                 lineThree->x1() + lineThree->length() *
                                 qCos(qDegreesToRadians(lineThree->angle())),
                                 lineThree->y1() + lineThree->length() *
                                 qSin(qDegreesToRadians(lineThree->angle())))
                             );
            lineThree->setAngle(lineThree->angle() - 180.0);

            QLineF* lineFour = new QLineF();
            lineFour->setP1(QPointF(crntX + crntLength / 1.5 * crntCos,
                                    crntY + crntLength / 1.5 * crntSin));
            lineFour->setLength(crntLength / 3.0);
            lineFour->setAngle(crntAngle);

            newLines.append(lineOne);
            newLines.append(lineTwo);
            newLines.append(lineThree);
            newLines.append(lineFour);

            obsltLines.append(*line);
        }

        for (auto line = newLines.cbegin(), listEnd = newLines.cend();
             line != listEnd; ++line)
        {
            mKochTree.insert(**line);
            lines.append(*line);
        }

        for (auto line = obsltLines.cbegin(), listEnd = obsltLines.cend();
             line != listEnd; ++line)
        {
            lines.removeOne(*line);

            delete *line;
        }
    }

    // Free resources here, they're in tree.
    for (auto line = lines.cbegin(), listEnd = lines.cend();
         line != listEnd; ++line)
    {
        delete *line;
    }

    for (auto newLine = newLines.cbegin(), listEnd = newLines.cend();
         newLine != listEnd; ++newLine)
    {
        delete *newLine;
    }

    for (auto obsltLine = obsltLines.cbegin(), listEnd = obsltLines.cend();
         obsltLine != listEnd; ++obsltLine)
    {
        delete *obsltLine;
    }
}
