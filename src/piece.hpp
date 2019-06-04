#pragma once
#include <array>   // array
#include <utility> // pair, make_pair

enum class PieceName : char {
	f = 'f', i = 'i', l = 'l', n = 'n', p = 'p', t = 't',
	u = 'u', v = 'v', w = 'w', x = 'x', y = 'y', z = 'z'
};

class Piece {
public:
	// Construct a piece with the given offsets and name.
	Piece(const std::array<std::pair<int, int>, 5>& a, PieceName pn)
			: offsets(a), name(pn) {}
	// Return the zero-indexed value corresponding to the piece.
	int getIndex() const;
	// Return the set of five x-y offsets defining the shape of the piece.
	std::array<std::pair<int, int>, 5> getOffsets() const;
	// Print the corresponding PieceName.
	friend std::ostream& operator<<(std::ostream& out, const Piece& p);

private:
	std::array<std::pair<int, int>, 5> offsets;
	PieceName name;
};
