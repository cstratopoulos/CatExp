#ifndef CATALANVIZ_HPP
#define CATALANVIZ_HPP

#include "catalanboard.hpp"

#include <QGraphicsScene>


/// Abstract base class for visualizing a Catalan board.
class CatalanViz {
public:
    CatalanViz(const CatalanBoard &board, QGraphicsScene &scene)
        : catBoard{board}, boardScene{scene} {}

    virtual ~CatalanViz() = default;

    enum class Type {
        path, tree, triang, ncPart,
    };

    /// Can implementdrawing a base/grid/skeleton for the visualization.
    virtual void drawSkeleton() {}

    /// Implements the particular visualization of the CatalanBoard.
    virtual void drawViz() = 0;

    std::size_t boardDim() const { return catBoard.dimension(); }

protected:
    const CatalanBoard &catBoard;
    QGraphicsScene &boardScene;
};

#endif // CATALANVIZ_HPP
