#include "piece.hpp" // Piece
#include "state.hpp" // operator<<
#include <map>       // map

int Piece::getIndex() const {
	std::map<PieceName, int> pieceIndex = {
		{PieceName::f, 0}, {PieceName::i, 1}, {PieceName::l, 2},
		{PieceName::n, 3}, {PieceName::p, 4}, {PieceName::t, 5},
		{PieceName::u, 6}, {PieceName::v, 7}, {PieceName::w, 8},
		{PieceName::x, 9}, {PieceName::y, 10}, {PieceName::z, 11}
	};
	return pieceIndex[name];
}

std::array<std::pair<int, int>, 5> Piece::getOffsets() const {
    return offsets;
}

std::ostream& operator<<(std::ostream& out, const Piece& p) {
	return out << p.name;
}
