#include "catalanboard.hpp"

#include <random>

using std::size_t;
using std::string;

/// Returns a reference to the cursor coordinate that is related to dir.
size_t &CatalanBoard::cursorCoordRef(Direc dir)
{ return (dir == Direc::east) ? cursor.x : cursor.y; }

/// Returns a reference to the counter that is related to dir.
size_t &CatalanBoard::counterRef(Direc dir)
{ return (dir == Direc::east) ? eastCount : southCount; }

/// Make a move in the Direc dir. Returns true if the move was completed,
/// false for an illegal move that was not performed.
bool CatalanBoard::makeMove(Direc dir)
{
    size_t &coordCount = counterRef(dir);
    if (coordCount == dim)
        return false;

    size_t &coord = cursorCoordRef(dir);
    if (&coord == &cursor.y && cursor.y == cursor.x)
        return false;

    ++coordCount;
    ++coord;
    moves.push_back(dir);

    return true;
}

/// Undo the last move. Has no effect if the path is empty.
void CatalanBoard::undoMove()
{
    if (moves.empty())
        return;

    Direc dir = moves.back();
    --cursorCoordRef(dir);
    --counterRef(dir);
    moves.pop_back();
}

/// Clear any existing path.
void CatalanBoard::clear() { *this = CatalanBoard(dim); }

/// Resizes the board.
/// If newDim is less than the current dim, the path is cleared.
/// If it is greater, the board is expanded and a path that may previously
/// have been complete can now be extended.
/// Calling it with the same size has no effect.
/// @todo smart truncation for size decrease.
void CatalanBoard::resize(size_t newDim)
{
    if (newDim == 0) {
        *this = CatalanBoard();
        return;
    }

    if (newDim == dim)
        return;

    if (newDim < dim) {
        *this = CatalanBoard(newDim);
    } else
        dim = newDim;
}

/// Randomly generate a path. If a partial or empty path is present, it will
/// be completed. A complete path will be cleared and restarted.
void CatalanBoard::random()
{
    if (finished())
        clear();

    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist(0, 1);

    while (!finished()) {
        if (dist(mt) == 0)
            if (makeMove(Direc::east))
                continue;

        makeMove(Direc::south);
    }
}

/// Set the path determined by the characters in the string moves.
/// The first character of moves shall be the east move character; all others
/// do a south move. The path need not be complete or even of correct
/// dimension; this method performs as many valid moves as possible from the
/// start of the string until the path is complete or the end of the string
/// is reached. The resident path is cleared.
void CatalanBoard::setPath(const string &moves)
{
    clear();

    char eastChar{moves.front()};

    for (char c : moves) {
        if (c == eastChar)
            makeMove(Direc::east);
        else
            makeMove(Direc::south);

        if (finished())
            break;
    }
}

/// Returns true iff the current path is complete.
bool CatalanBoard::finished() const
{ return cursor.x == dim && cursor.y == dim; }

/// Returns a string corresponding to the current path.
/// The string consists of letters e for east moves and s for south moves.
string CatalanBoard::pathString() const
{
    string result;
    result.reserve(moves.size());

    for (Direc dir : moves)
        if (dir == Direc::east)
            result.push_back('e');
        else
            result.push_back('s');

    return result;
}




