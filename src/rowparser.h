#pragma once

#include <iostream>   // istream, ostream
#include <vector>     // vector
#include <functional> // function

// Forward declarations
template <typename T>
class RowParser;

template <typename T>
std::ostream& operator<<(std::ostream& out, const RowParser<T>& rp);

template <typename T>
std::istream& operator>>(std::istream& in, RowParser<T>& rp);


template <typename T>
class RowParser {
public:
	RowParser(std::function<T(char)> f);
    std::vector<T> getRow() const;
    friend std::ostream& operator<< <T>(std::ostream& out, const RowParser& rp);
	friend std::istream& operator>> <T>(std::istream& in, RowParser& rp);
private:
	std::vector<T> row;
	std::function<T(char)> converter;
};

#include "rowparser_impl.hpp"
