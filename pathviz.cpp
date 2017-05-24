#include "pathviz.hpp"

using std::size_t;

/// Constructs the base CatalanViz and initializes some commonly used pens.
PathViz::PathViz(const CatalanBoard &board, QGraphicsScene &scene)
    : CatalanViz(board, scene)
{
    borderPen.setWidth(2);

    gridPen.setWidth(2);
    gridPen.setColor(Qt::lightGray);

    diagPen = gridPen;
    diagPen.setStyle(Qt::DashLine);

    pathPen.setWidth(2);
    pathPen.setColor(Qt::red);
}

/// Draws a square grid with a bounding box and diagonal line.
void PathViz::drawSkeleton()
{
    const auto loopMax = boardDim();
    const auto gMax = gridMax();

    for (size_t x = 0; x <= loopMax; ++x) {
        auto xVals = coordScale(x);
        boardScene.addLine(xVals, 0, xVals, gMax, gridPen);
    }

    for (size_t y = 0; y <= loopMax; ++y) {
        auto yVals = coordScale(y);
        boardScene.addLine(0, yVals, gMax, yVals, gridPen);
    }

    boardScene.addLine(0, 0, gMax, gMax, diagPen);
    boardScene.addRect(0, 0, gMax, gMax, borderPen, QBrush());
}

/// Draws the Catalan Path thus far.
void PathViz::drawViz()
{
    drawSkeleton();

    Coord cur(0, 0);
    Coord prev(0, 0);

    const auto &moveList = catBoard.currentPath();
    for (CatalanBoard::Direc dir : moveList) {
        if (dir == CatalanBoard::Direc::east)
            cur.x += gridStep;
        else
            cur.y += gridStep;

        boardScene.addLine(prev.x, prev.y, cur.x, cur.y, pathPen);
        prev = cur;
    }
}
