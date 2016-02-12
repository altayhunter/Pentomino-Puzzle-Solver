#include <iostream> // cout
#include <memory>   // unique_ptr
#include <thread>   // thread
#include <future>   // async, future
#include <list>     // list
#include "state.h"  // State
#include "matrix.h" // Matrix

using namespace std;

// Function declarations
unique_ptr<Matrix<State>> checkFirstColumn(const Matrix<State>& m);
unique_ptr<Matrix<State>> selectRow(const size_t rowN, Matrix<State> m);

// make_unique is not part of the standard in C++11
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// Launch the threads to find all results in parallel
// TODO: Print results as found; not only once all are computed.
void launchThreads(const Matrix<State>& m) {
	list<future<unique_ptr<Matrix<State>>>> results;
	for (size_t i = 0; i < m.numRows(); ++i) {
		if (m[i][0] == State::full) {
			results.push_back(async(launch::async, selectRow, i, m));
		}
	}
	for (auto&& f : results) {
		auto p = f.get();
		if (p) {
			cout << *p << endl;
		}
	}
}

unique_ptr<Matrix<State>> checkFirstColumn(const Matrix<State>& m) {
	auto colN = m.validColumnWithFewest(State::full, State::invalid);
	if (colN < m.numCols()) {
		// Iterate rows, call selectRow unconditionally with each 1
		for (size_t i = 0; i < m.numRows(); ++i) {
			if (m[i][colN] == State::full) {
				// If selectRow finds something, return whatever it found
				auto n = selectRow(i, m);
				if (n) {
					return n;
				}
			}
		}
	}
	return nullptr;
}

unique_ptr<Matrix<State>> selectRow(const size_t rowN, Matrix<State> m) {
	// Grab given row
	auto row = m[rowN];
	// First check if row is all 1s; if so we're done!
	if (!m.inRow(State::empty, rowN)) {
		return make_unique<Matrix<State>>(row);
	}
	// Remove "matching" rows
	m.setMatchingRows(rowN, State::full, State::invalid);
	// Remove all columns covered by "row"
	for (int i = m.numCols() - 1; i >= 0; --i) {
		if (row[i] == State::full) {
			m.setCol(i, State::invalid);
		}
	}
	// If empty, return null to indicate a dead end
	if (m.isEntirely(State::invalid)) {
		return nullptr;
	// Else check the next remaining column
	} else {
		auto n = checkFirstColumn(m);
		if (n) {
			n->addRow(row);
		}
		return n;
	}
}

int main(int argc, char **argv) {
/*
	// Testcase from the pdf
	Matrix<State> matrix = {
		{State::empty, State::empty, State::full,  State::empty, State::full,  State::full,  State::empty},
		{State::full,  State::empty, State::empty, State::full,  State::empty, State::empty, State::full },
		{State::empty, State::full,  State::full,  State::empty, State::empty, State::full,  State::empty},
		{State::full,  State::empty, State::empty, State::full,  State::empty, State::empty, State::empty},
		{State::empty, State::full,  State::empty, State::empty, State::empty, State::empty, State::full },
		{State::empty, State::empty, State::empty, State::full,  State::full,  State::empty, State::full },
	};
*/
	Matrix<State> matrix("puzzle", [](char c) {
			return c == '0' ? State::empty :
			       c == '1' ? State::full :
			       State::invalid;
	});

	launchThreads(matrix);

	return 0;
}
