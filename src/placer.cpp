#include "placer.hpp" // Placer
#include <algorithm>  // remove_if
#include <map>        // map

using std::map;
using std::pair;
using std::remove_if;
using std::vector;

map<PieceName, int> pieceIndex = {
	{PieceName::f, 0}, {PieceName::i, 1}, {PieceName::l, 2},
	{PieceName::n, 3}, {PieceName::p, 4}, {PieceName::t, 5},
	{PieceName::u, 6}, {PieceName::v, 7}, {PieceName::w, 8},
	{PieceName::x, 9}, {PieceName::y, 10}, {PieceName::z, 11}
};

// Flatten the given 2D vector into a single vector.
template<typename T>
vector<T> flatten(const vector<vector<T>>& original) {
	vector<T> flat;
	for(const auto &row : original) {
		flat.insert(flat.end(), row.begin(), row.end());
	}
	return flat;
}

// Append the piece indexes corresponding to the
// given piece to the end of the given vector.
void appendPieceIndex(vector<State>& v, Piece piece) {
	vector<State> pieces = vector<State>(12, State::empty);
	pieces[piece.getIndex()] = State::full;
	v.insert(v.end(), pieces.begin(), pieces.end());
}

// Remove all invalid members from the given vector.
void stripInvalids(vector<State>& v) {
	v.erase(remove_if(v.begin(), v.end(), [](State s) {
				return s == State::invalid;
			}), v.end());
}

bool Placer::finished() {
	while (!canPlace()) {
		if (!increment()) {
			return true;
		}
	}
	return false;
}

vector<State> Placer::get() {
	vector<vector<State>> copy = board;
	for (pair<int, int> offset : piece.getOffsets()) {
		int x = position.first + offset.first;
		int y = position.second + offset.second;
		copy[y][x] = State::full;
	}
	increment();
	vector<State> flat = flatten(copy);
	appendPieceIndex(flat, piece);
	stripInvalids(flat);
	return flat;
}

bool Placer::canPlace() const {
	for (pair<int, int> offset : piece.getOffsets()) {
		if (!vacant(offset)) {
			return false;
		}
	}
	return true;
}

bool Placer::vacant(pair<int, int> offset) const {
	int x = position.first + offset.first;
	int y = position.second + offset.second;
	if (y >= board.size() || x >= board[y].size()) {
		return false;
	}
	return board[y][x] == State::empty;
}

bool Placer::increment() {
	bool x_max = position.first >= board[position.second].size() - 1;
	bool y_max = position.second >= board.size() - 1;
	if (x_max) {
		if (y_max) {
			return false;
		} else {
			position.first = 0;
			position.second++;
		}
	} else {
		position.first++;
	}
	return true;
}
