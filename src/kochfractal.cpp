#include <QImage>
#include <QList>
#include <QPainter>
#include <QtMath>

#include "kochfractal.hpp"
#include "kochline.hpp"
#include "tools.hpp"

KochFractal::KochFractal(int width, int height)
    : mIterations(DEFAULT_ITERATIONS),
      mKochTree(Tools::getEquilateralTriangleLines(width, height))
{

}

KochFractal::KochFractal(QSize size)
    : KochFractal(size.width(), size.height())
{

}

bool KochFractal::setIterations(int iterations)
{
    if (iterations < MINIMUM_ITERATIONS || iterations > MAXIMUM_ITERATIONS)
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

KochTree* KochFractal::getTree()
{
    return &mKochTree;
}

QImage KochFractal::getKochSnowflake()
{
    // TODO: Check if children are empty.
    KochLine initialLine =
            this->getTree()->getRoot()->getChildren().first()->getLine();

    // Length of initial line is (width - 200).
    int size = static_cast<int>(initialLine.getLength()) + 200;
    QImage image = Tools::getImage(size, size);

    this->_getKochSnowflake(this->getTree()->getRoot(), &image);

    return image;
}

void KochFractal::_getKochSnowflake(KochNode* node, QImage* image)
{
    if (node->hasChildren())
    {
        QList<KochNode*> childNodes = node->getChildren();

        for (auto crntChildNode = childNodes.cbegin(), listEnd = childNodes.cend();
             crntChildNode != listEnd; ++crntChildNode)
        {
            _getKochSnowflake(*crntChildNode, image);
        }
    }
    else
    {
        QPainter painter;

        painter.begin(image);
        painter.drawLine(node->getLine().getLine());
        painter.end();
    }
}

QSize KochFractal::getTreeImageSize()
{
    int leavesCount = 3 *
            static_cast<int>(qPow(4.0, static_cast<double>(mIterations - 1)));

    return QSize(leavesCount * VERTICAL_GAP,
                 (mIterations + 1) * HORIZONTAL_GAP);
}

void KochFractal::process()
{
    QList<KochLine*> lines;

    // Initialize lines.
    QList<KochNode*> rootChildren = mKochTree.getRoot()->getChildren();
    for (auto node = rootChildren.cbegin(), listEnd = rootChildren.cend();
         node != listEnd; ++node)
    {
        lines.append(new KochLine((*node)->getLine()));
    }

    for (int iterations = this->getIterations();
         iterations > MINIMUM_ITERATIONS; --iterations)
    {
        QList<KochLine*> newLines, obsltLines;

        for (auto line = lines.cbegin(), listEnd = lines.cend();
             line != listEnd; ++line)
        {
            double crntX = (*line)->getX1();
            double crntY = (*line)->getY1();
            double crntLength = (*line)->getLength();
            double crntAngle = (*line)->getAngle();
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

            KochLine lineOne;
            lineOne.setP1(QPointF(crntX, crntY));
            lineOne.setLength(crntLength / 3.0);
            lineOne.setAngle(crntAngle);

            KochLine lineTwo;
            lineTwo.setP1(QPointF(crntX + crntLength / 3.0 * crntCos,
                                  crntY + crntLength / 3.0 * crntSin));
            lineTwo.setLength(crntLength / 3.0);
            lineTwo.setAngle(crntAngle + 60.0);

            KochLine lineThree;
            lineThree.setP1(QPoint(crntX + crntLength / 1.5 * crntCos,
                                   crntY + crntLength / 1.5 * crntSin));
            lineThree.setLength(crntLength / 3.0);
            lineThree.setAngle(crntAngle + 120.0);
            // Fix line orientation
            lineThree.setP1(lineThree.getP2());
            lineThree.setAngle(lineThree.getAngle() - 180.0);

            KochLine lineFour;
            lineFour.setP1(QPointF(crntX + crntLength / 1.5 * crntCos,
                                   crntY + crntLength / 1.5 * crntSin));
            lineFour.setLength(crntLength / 3.0);
            lineFour.setAngle(crntAngle);

            mKochTree.insert(lineOne);
            mKochTree.insert(lineTwo);
            mKochTree.insert(lineThree);
            mKochTree.insert(lineFour);

            newLines.append(new KochLine(lineOne));
            newLines.append(new KochLine(lineTwo));
            newLines.append(new KochLine(lineThree));
            newLines.append(new KochLine(lineFour));

            obsltLines.append(*line);
        }

        for (auto line = newLines.cbegin(), listEnd = newLines.cend();
             line != listEnd; ++line)
        {
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
}
