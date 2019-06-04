#include "parser.hpp"
#include <vector>     // vector
#include "state.hpp"  // State
#include "piece.hpp"  // Piece
#include "placer.hpp" // Placer

using std::vector;
using std::string;

Piece pieces[] = {
	Piece({{{1,0},{2,0},{0,1},{1,1},{1,2}}}, PieceName::f),  // normal f
	Piece({{{1,0},{0,1},{1,1},{2,1},{2,2}}}, PieceName::f),  // rotated f
	Piece({{{1,0},{1,1},{2,1},{0,2},{1,2}}}, PieceName::f),  // rotated f
	Piece({{{0,0},{0,1},{1,1},{1,2},{2,1}}}, PieceName::f),  // rotated f
	Piece({{{0,0},{1,0},{1,1},{2,1},{1,2}}}, PieceName::f),  // flipped f
	Piece({{{2,0},{0,1},{1,1},{2,1},{1,2}}}, PieceName::f),  // rotated f
	Piece({{{1,0},{0,1},{1,1},{1,2},{2,2}}}, PieceName::f),  // rotated f
	Piece({{{1,0},{0,1},{1,1},{2,1},{0,2}}}, PieceName::f),  // rotated f
	Piece({{{0,0},{0,1},{0,2},{0,3},{0,4}}}, PieceName::i),  // vertical i
	Piece({{{0,0},{1,0},{2,0},{3,0},{4,0}}}, PieceName::i),  // horizontal i
	Piece({{{0,0},{0,1},{0,2},{0,3},{1,3}}}, PieceName::l),  // normal l
	Piece({{{0,0},{1,0},{2,0},{3,0},{0,1}}}, PieceName::l),  // rotated l
	Piece({{{0,0},{1,0},{1,1},{1,2},{1,3}}}, PieceName::l),  // rotated l
	Piece({{{0,1},{1,1},{2,1},{3,1},{3,0}}}, PieceName::l),  // rotated l
	Piece({{{1,0},{1,1},{1,2},{1,3},{0,3}}}, PieceName::l),  // flipped l
	Piece({{{0,0},{0,1},{1,1},{2,1},{3,1}}}, PieceName::l),  // rotated l
	Piece({{{0,0},{1,0},{0,1},{0,2},{0,3}}}, PieceName::l),  // rotated l
	Piece({{{0,0},{1,0},{2,0},{3,0},{3,1}}}, PieceName::l),  // rotated l
	Piece({{{1,0},{0,1},{1,1},{2,0},{3,0}}}, PieceName::n),  // normal n
	Piece({{{0,0},{1,0},{2,0},{2,1},{3,1}}}, PieceName::n),  // rotated n
	Piece({{{1,0},{1,1},{0,2},{1,2},{0,3}}}, PieceName::n),  // rotated n
	Piece({{{0,0},{1,0},{1,1},{2,1},{3,1}}}, PieceName::n),  // rotated n
	Piece({{{0,0},{0,1},{1,1},{1,2},{1,3}}}, PieceName::n),  // flipped n
	Piece({{{2,0},{3,0},{0,1},{1,1},{2,1}}}, PieceName::n),  // rotated n
	Piece({{{0,0},{0,1},{0,2},{1,2},{1,3}}}, PieceName::n),  // rotated n
	Piece({{{0,1},{0,2},{0,3},{1,0},{1,1}}}, PieceName::n),  // rotated n
	Piece({{{0,0},{1,0},{0,1},{1,1},{0,2}}}, PieceName::p),  // normal p
	Piece({{{0,0},{1,0},{2,0},{1,1},{2,1}}}, PieceName::p),  // rotated p
	Piece({{{1,0},{0,1},{1,1},{0,2},{1,2}}}, PieceName::p),  // rotated p
	Piece({{{0,0},{1,0},{0,1},{1,1},{2,1}}}, PieceName::p),  // rotated p
	Piece({{{0,0},{1,0},{0,1},{1,1},{1,2}}}, PieceName::p),  // flipped p
	Piece({{{1,0},{2,0},{0,1},{1,1},{2,1}}}, PieceName::p),  // rotated p
	Piece({{{0,0},{0,1},{1,1},{0,2},{1,2}}}, PieceName::p),  // rotated p
	Piece({{{0,0},{1,0},{2,0},{0,1},{1,1}}}, PieceName::p),  // rotated p
	Piece({{{0,0},{1,0},{2,0},{1,1},{1,2}}}, PieceName::t),  // normal t
	Piece({{{2,0},{0,1},{1,1},{2,1},{2,2}}}, PieceName::t),  // rotated t
	Piece({{{1,0},{1,1},{0,2},{1,2},{2,2}}}, PieceName::t),  // rotated t
	Piece({{{0,0},{0,1},{1,1},{2,1},{0,2}}}, PieceName::t),  // rotated t
	Piece({{{0,0},{2,0},{0,1},{1,1},{2,1}}}, PieceName::u),  // normal u
	Piece({{{0,0},{1,0},{0,1},{0,2},{1,2}}}, PieceName::u),  // rotated u
	Piece({{{0,0},{1,0},{2,0},{0,1},{2,1}}}, PieceName::u),  // rotated u
	Piece({{{0,0},{1,0},{1,1},{0,2},{1,2}}}, PieceName::u),  // rotated u
	Piece({{{0,0},{0,1},{0,2},{1,2},{2,2}}}, PieceName::v),  // normal v
	Piece({{{0,0},{1,0},{2,0},{0,1},{0,2}}}, PieceName::v),  // rotated v
	Piece({{{0,0},{1,0},{2,0},{2,1},{2,2}}}, PieceName::v),  // rotated v
	Piece({{{2,0},{2,1},{0,2},{1,2},{2,2}}}, PieceName::v),  // rotated v
	Piece({{{0,0},{0,1},{1,1},{1,2},{2,2}}}, PieceName::w),  // normal w
	Piece({{{1,0},{2,0},{0,1},{1,1},{0,2}}}, PieceName::w),  // rotated w
	Piece({{{0,0},{1,0},{1,1},{2,1},{2,2}}}, PieceName::w),  // rotated w
	Piece({{{2,0},{1,1},{2,1},{0,2},{1,2}}}, PieceName::w),  // rotated w
	Piece({{{1,0},{0,1},{1,1},{2,1},{1,2}}}, PieceName::x),  // normal x
	Piece({{{1,0},{0,1},{1,1},{1,2},{1,3}}}, PieceName::y),  // normal y
	Piece({{{2,0},{0,1},{1,1},{2,1},{3,1}}}, PieceName::y),  // rotated y
	Piece({{{0,0},{0,1},{0,2},{1,2},{0,3}}}, PieceName::y),  // rotated y
	Piece({{{0,0},{1,0},{2,0},{3,0},{1,1}}}, PieceName::y),  // rotated y
	Piece({{{0,0},{0,1},{1,1},{0,2},{0,3}}}, PieceName::y),  // flipped y
	Piece({{{0,0},{1,0},{2,0},{3,0},{2,1}}}, PieceName::y),  // rotated y
	Piece({{{1,0},{1,1},{0,2},{1,2},{1,3}}}, PieceName::y),  // rotated y
	Piece({{{1,0},{0,1},{1,1},{2,1},{3,1}}}, PieceName::y),  // rotated y
	Piece({{{0,0},{1,0},{1,1},{1,2},{2,2}}}, PieceName::z),  // normal z
	Piece({{{2,0},{0,1},{1,1},{2,1},{0,2}}}, PieceName::z),  // rotated z
	Piece({{{1,0},{2,0},{1,1},{0,2},{1,2}}}, PieceName::z),  // flipped z
	Piece({{{0,0},{0,1},{1,1},{2,1},{2,2}}}, PieceName::z)   // rotated z
};

vector<vector<State>> parsePuzzle(const string& puzzle) {
	vector<vector<State>> matrix;
	vector<State> row;
	for (char c : puzzle) {
		if (c == '\n') {
			matrix.push_back(row);
			row.clear();
		} else if (c == '0') {
			row.push_back(State::empty);
		} else {
			row.push_back(State::invalid);
		}
	}
	matrix.push_back(row);
	return matrix;
}

vector<vector<State>> getRows(const vector<vector<State>>& board) {
	vector<vector<State>> rows;
	for (Piece piece : pieces) {
		Placer placer(board, piece);
		while (!placer.finished()) {
			rows.push_back(placer.get());
		}
	}
	return rows;
}
