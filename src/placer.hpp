#pragma once
#include <vector>    // vector
#include <utility>   // pair, make_pair
#include "piece.hpp" // Piece
#include "state.hpp" // State

class Placer {
public:
	// Construct from the given board and piece.
	Placer(std::vector<std::vector<State>> board, Piece piece) : board(board), piece(piece) {}
	// Move to the next valid position, returning true if none exists.
	bool finished();
	// Return the board with the piece placed in the current position.
	std::vector<State> get();

private:
	// Return whether the piece can be placed at the current position.
	bool canPlace() const;
	// Return whether the given offset from position is a valid empty spot on the board.
	bool vacant(std::pair<int, int> offset) const;
	// Safely increment the position, returning false if at end.
	bool increment();

	// A 2D representation of the empty board.
	std::vector<std::vector<State>> board;
	// The piece that will be placed on every position on the board.
	Piece piece;
	// The coordinates of the top left corner of the piece.
	std::pair<int, int> position = std::make_pair(0, 0);
};
