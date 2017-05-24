#ifndef TRIANGVIZ_HPP
#define TRIANGVIZ_HPP

#include "catalanviz.hpp"

#include <QPolygonF>

/// For a Catalan board of dimension n, visualize triangulations
/// of a regular (n + 2)-gon.
class TriangViz : public CatalanViz {
public:
    TriangViz(const CatalanBoard &board, QGraphicsScene &scene);

    void drawSkeleton() override;
    void drawViz() override;

private:
    QPolygonF skelPolygon;
    static QPolygonF getPolygon(const CatalanBoard &board);

    QPen polygonPen;
    QPen triangPen;
    QPen lookPen;

    static constexpr std::size_t radius{200};
};

#endif // TRIANGVIZ_HPP
