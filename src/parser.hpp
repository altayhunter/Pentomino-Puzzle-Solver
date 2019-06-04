#include <vector>    // vector
#include "state.hpp" // State

// Convert the given string representation into a 2D vector of enums.
std::vector<std::vector<State>> parsePuzzle(const std::string& puzzle);

// Produce a row for every piece in every possible position.
std::vector<std::vector<State>> getRows(const std::vector<std::vector<State>>& board);
