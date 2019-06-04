#include "sparse_matrix.hpp" // SparseMatrix
#include "parser.hpp"        // getRows, parsePuzzle

int main(int argc, char **argv) {
	std::string puzzle =
			"-----------0-\n"
			"-----------00\n"
			"----00--0000-\n"
			"00000000000--\n"
			"00000000000--\n"
			"0000000000---\n"
			"00000000-----\n"
			"0000000------\n"
			"00---00------";
	SparseMatrix sm(getRows(parsePuzzle(puzzle)));
	sm.findSolution(0);

	return 0;
}
