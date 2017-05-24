#ifndef PATHVIZ_HPP
#define PATHVIZ_HPP

#include "catalanviz.hpp"

#include <QPen>

/// Visualizing Catalan paths on a grid.
class PathViz : public CatalanViz {
public:
    PathViz(const CatalanBoard &board, QGraphicsScene &scene);

    void drawSkeleton() override;
    void drawViz() override;

private:
    QPen borderPen;
    QPen gridPen;
    QPen diagPen;
    QPen pathPen;

    static constexpr std::size_t gridStep{25};

    std::size_t coordScale(std::size_t coord) const
    { return gridStep * coord; }

    std::size_t gridMax() const { return coordScale(boardDim()); }
};

#endif // PATHVIZ_HPP
