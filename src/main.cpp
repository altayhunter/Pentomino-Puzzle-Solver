#include "sparse_matrix.hpp" // SparseMatrix
#include "parser.hpp"        // getRows, parsePuzzle

constexpr char puzzle28[] =
		"-00--0000-\n"
		"00--000000\n"
		"00--000000\n"
		"000--00000\n"
		"00000--000\n"
		"000000--00\n"
		"000000--00\n"
		"-0000--00-";

constexpr char puzzle42[] =
		"-----------0-\n"
		"-----------00\n"
		"----00--0000-\n"
		"00000000000--\n"
		"00000000000--\n"
		"0000000000---\n"
		"00000000-----\n"
		"0000000------\n"
		"00---00------";

constexpr char puzzle54[] =
		"0000-0000\n"
		"000---000\n"
		"000---000\n"
		"00-----00\n"
		"000000000\n"
		"000000000\n"
		"000000000\n"
		"000000000";

int main(int argc, char **argv) {
	SparseMatrix sm(getRows(parsePuzzle(puzzle54)));
	sm.findSolution(0);

	return 0;
}

// TODO: Move pretty_print.py into here to deduplicate the puzzle.
