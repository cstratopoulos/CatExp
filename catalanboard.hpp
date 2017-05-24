#ifndef CATALANBOARD_HPP
#define CATALANBOARD_HPP

#include <string>
#include <vector>

#include <cstddef>

struct Coord {
    Coord() = default;
    Coord(std::size_t x_, std::size_t y_) : x{x_}, y{y_} {}

    std::size_t x{0};
    std::size_t y{0};
};

inline bool operator==(const Coord &c, const Coord &d)
{ return c.x == d.x && c.y == d.y; }

/// Representation of a board on which Catalan paths may be computed.
class CatalanBoard {
public:
    CatalanBoard(std::size_t dim_ = 0) : dim{dim_} {}

    enum class Direc {
        east, south
    };

    bool makeMove(Direc dir);
    void undoMove();

    void clear();
    void resize(std::size_t newDim);
    void random();

    void setPath(const std::string &moves);

    bool finished() const;

    std::size_t eastRemaining() const { return dim - cursor.x; }
    std::size_t southRemaining() const { return dim - cursor.y; }

    Coord currentPos() const { return cursor; }

    const std::vector<Direc> &currentPath() const { return moves; }

    std::string pathString() const;

    std::size_t dimension() const { return dim; }

private:
    std::size_t dim{0};

    Coord cursor{Coord(0, 0)};

    std::vector<Direc> moves{};
    std::size_t eastCount{0};
    std::size_t southCount{0};

    std::size_t &cursorCoordRef(Direc dir);
    std::size_t &counterRef(Direc dir);
};

#endif // CATALANBOARD_HPP
