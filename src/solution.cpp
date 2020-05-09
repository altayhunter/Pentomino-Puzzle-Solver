#include "solution.hpp"   // Solution
#include "columnnode.hpp" // ColumnNode
#include "node.hpp"       // Node
#include "piece.hpp"      // PieceName
#include <algorithm>      // max_element
#include <array>          // array
#include <iostream>       // cout

using std::array;
using std::cout;
using std::string;
using std::vector;

Solution::Solution(const std::vector<Node*>& rows) {
	solution.reserve(12);
	for (Node* row : rows) {
		vector<int> piece;
		piece.reserve(5);
		piece.push_back(row->head()->id());
		for (Node& n : *row) {
			piece.push_back(n.head()->id());
		}
		solution.push_back(piece);
	}
}

void Solution::print() const {
	for (const vector<int>& piece : solution) {
		cout << "[";
		for (int square : piece) {
			cout << square << ",";
		}
		cout << "\b],";
	}
	cout << "\b ";
}

PieceName Solution::fromIndex(int index) {
	constexpr PieceName pieceNames[] = {
		PieceName::f, PieceName::i, PieceName::l, PieceName::n,
		PieceName::p, PieceName::t, PieceName::u, PieceName::v,
		PieceName::w, PieceName::x, PieceName::y, PieceName::z
	};
	return pieceNames[index - 60];
}

void Solution::print(const std::string& format, int pieces) const {
	array<char, 60> puzzle;
	puzzle.fill('0');
	for (int i = 0; i < solution.size() && i < pieces; i++) {
		const vector<int>& piece = solution[i];
		PieceName pn = fromIndex(*max_element(piece.begin(), piece.end()));
		for (int square : piece) {
			if (square < 60) {
				puzzle[square] = static_cast<char>(pn);
			}
		}
	}
	int index = 0;
	for (char c : format) {
		if (c == '0') {
			cout << puzzle[index];
			index++;
		} else {
			cout << c;
		}
	}
	cout << "\n\n";
}
