#pragma once

#include <vector>      // vector
#include <ostream>     // ostream
#include <string>      // string
#include <functional>  // function

// Forward declarations
template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m);


template <typename T>
class Matrix {
public:
	// Constructors
	Matrix(size_t colN, size_t rowN);
	Matrix(std::vector<T> row);
	Matrix(const std::initializer_list<std::initializer_list<T>>& values);
	Matrix(std::string folder, std::function<T(char)> f);
	Matrix(const Matrix& m) = default;
	Matrix& operator=(const Matrix& m) = default;
	Matrix(Matrix&& m) = default;
	~Matrix() = default;
	// Modifiers
	void setRow(size_t rowN, T value);
	void setCol(size_t colN, T value);
	void addRow(const std::vector<T>& row);
	void setMatchingRows(size_t rowN, T match, T set);
	void removeRow(size_t rowN);
	void removeCol(size_t colN);
	void removeMatchingRows(const std::vector<T>& row);
	// Const methods
	bool isEmpty() const;
	bool isEntirely(T value) const;
	size_t validColumnWithFewest(T value, T invalid) const;
	bool inRow(T value, size_t rowN) const;
	bool inCol(T value, size_t colN) const;
	size_t numRows() const;
	size_t numCols() const;
	const std::vector<T> operator[](size_t rowN) const;
private:
	// Member variables
	std::vector<std::vector<T>> elements;
	// Friends
	friend std::ostream& operator<< <T>(std::ostream& out, const Matrix& m);
};

#include "matrix_impl.hpp"
