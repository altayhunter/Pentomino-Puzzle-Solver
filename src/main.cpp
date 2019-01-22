#include "sparse_matrix.hpp" // SparseMatrix
#include "rowparser.hpp"     // RowParser
#include <dirent.h>          // DIR, dirent, opendir, readdir, closedir
#include <cassert>           // assert
#include <fstream>           // ifstream

// Return a 2D vector representation of the contents of the given folder.
std::vector<std::vector<State>> readFolder(std::string folder) {
	DIR *dir = opendir(folder.c_str());
	assert(dir);
	std::vector<std::vector<State>> data;
	while (struct dirent* ent = readdir(dir)) {
		// Skip hidden and system folders
		if (ent->d_name[0] == '.') {
			continue;
		}
		RowParser<State> rp([](char c) {
			return c == '0' ? State::empty :
					c == '1' ? State::full :
					State::invalid;
		});
		std::ifstream fin(folder + "/" + std::string(ent->d_name));
		while (fin.good()) {
			fin >> rp;
			data.push_back(rp.getRow());
		}
		fin.close();
	}
	closedir(dir);
	return data;
}

int main(int argc, char **argv) {
	/*
	// Testcase without any solutions
	SparseMatrix no_solution({
		{State::full,  State::full,  State::full,  State::full,  State::empty, State::empty, State::empty},
		{State::empty, State::empty, State::empty, State::full,  State::full,  State::full,  State::full },
	});
	// Testcase with multiple solutions
	SparseMatrix two_solutions({
		{State::full,  State::full,  State::full,  State::empty, State::empty, State::empty, State::empty},
		{State::empty, State::empty, State::empty, State::full,  State::full,  State::empty, State::empty},
		{State::empty, State::empty, State::empty, State::empty, State::empty, State::full,  State::full },
		{State::full,  State::full,  State::full,  State::full,  State::full,  State::empty, State::empty},
	});
	// Testcase from the pdf
	SparseMatrix matrix({
		{State::empty, State::empty, State::full,  State::empty, State::full,  State::full,  State::empty},
		{State::full,  State::empty, State::empty, State::full,  State::empty, State::empty, State::full },
		{State::empty, State::full,  State::full,  State::empty, State::empty, State::full,  State::empty},
		{State::full,  State::empty, State::empty, State::full,  State::empty, State::empty, State::empty},
		{State::empty, State::full,  State::empty, State::empty, State::empty, State::empty, State::full },
		{State::empty, State::empty, State::empty, State::full,  State::full,  State::empty, State::full },
	});
	no_solution.findSolution(0);
	two_solutions.findSolution(0);
	matrix.findSolution(0);
	*/

	SparseMatrix sm(readFolder("puzzle"));
	sm.findSolution(0);

	return 0;
}
