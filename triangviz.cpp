#include "triangviz.hpp"

#include <QVector>
#include <QPointF>
#include <QtMath>

#include <vector>

using std::vector;

TriangViz::TriangViz(const CatalanBoard &board, QGraphicsScene &scene)
    : CatalanViz(board, scene),
      skelPolygon(getPolygon(board))
{
    polygonPen.setWidth(2);

    triangPen.setWidth(2);
    triangPen.setColor(Qt::red);

    lookPen.setWidth(3);
    lookPen.setColor(Qt::darkGray);
    lookPen.setStyle(Qt::SolidLine);
}

/// Draws the polygon on which a triangulation will be computed.
void TriangViz::drawSkeleton()
{
    skelPolygon = getPolygon(catBoard);
    boardScene.clear();
    boardScene.addPolygon(skelPolygon, polygonPen);

    const QVector<QPointF> &polyPts = skelPolygon;

    auto vxRadius = 3;
    Q_FOREACH (const QPointF &pt, polyPts) {
        boardScene.addEllipse(pt.x() - vxRadius, pt.y() - vxRadius,
                              2 * vxRadius, 2 * vxRadius,
                              QPen(), QBrush(Qt::SolidPattern));
    }
}

void TriangViz::drawViz()
{
    drawSkeleton();

    auto dim = boardDim();
    if (dim == 0)
        return;

    const auto &moveList = catBoard.currentPath();
    const QVector<QPointF> &polyCoords = skelPolygon;
    vector<int> availIndices;
    auto numVxs = polyCoords.size();

    for (auto i = 0; i < numVxs; ++i)
        availIndices.push_back(i);

    auto coWidth = dim;

    for (auto dir : moveList)
        if (dir == CatalanBoard::Direc::east)
            --coWidth;
        else {
            if (availIndices.empty())
                break;

            auto numLeft = availIndices.size();
            const auto &cwVx = polyCoords[coWidth];
            const auto &otherVx = polyCoords[availIndices[(coWidth + 2) % numLeft]];
            if (otherVx == polyCoords[(coWidth + 1) % numVxs] ||
                otherVx == polyCoords[(coWidth + numVxs -1) % numVxs])
                continue;

            boardScene.addLine(QLineF(cwVx, otherVx), triangPen);
            availIndices.erase(availIndices.begin() + ((coWidth + 1) % numLeft));
        }

    auto CWpt = skelPolygon[coWidth];

    auto hlRadius = 6;
    boardScene.addEllipse(CWpt.x() - hlRadius, CWpt.y() - hlRadius,
                          2 * hlRadius, 2 * hlRadius,
                          lookPen);
}

/// Returns a regular n+2 gon where n is board.dimension().
QPolygonF TriangViz::getPolygon(const CatalanBoard &board)
{
    auto vxCount = board.dimension() + 2;
    QPolygonF result{};

    result.reserve(vxCount);

    for (std::size_t i = 0; i < vxCount; ++i) {
        result <<QPointF (radius * qCos((2 * 3.14 * i) / vxCount),
                          radius * qSin((2 * 3.14 * i) / vxCount));
    }

    return result;
}
