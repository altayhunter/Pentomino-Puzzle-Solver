#include <algorithm>   // for_each, find_if, max_element
#include <stdexcept>   // out_of_range
#include <fstream>     // ifstream
#include <dirent.h>    // dir, dirent, opendir, readdir, closedir
#include "rowparser.h" // RowParser

template <typename T>
Matrix<T>::Matrix(size_t colN, size_t rowN) :
	elements(rowN, std::vector<T>(colN)) {	
}

template <typename T>
Matrix<T>::Matrix(std::vector<T> row) {
	addRow(row);
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &values) {
	elements.reserve(values.size());
	for (const auto& row : values) {
		addRow(row);
	}
}

template <typename T>
Matrix<T>::Matrix(std::string folder, std::function<T(char)> f) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(folder.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			// Skip hidden and system folders
			if (ent->d_name[0] == '.') {
				continue;
			}
			RowParser<T> rp(f);
			std::ifstream fin(folder + "/" + std::string(ent->d_name));
			while (fin.good()) {
				fin >> rp;
				addRow(rp.getRow());
			}
			fin.close();
		}
		closedir(dir);
	}
}

template <typename T>
void Matrix<T>::setRow(size_t rowN, T value) {
	const auto &begin = elements.at(rowN).begin();
	const auto &end = elements.at(rowN).end();
	std::fill(begin, end, value);
}

template <typename T>
void Matrix<T>::setCol(size_t colN, T value) {
	std::for_each(elements.begin(), elements.end(),
		[&colN, &value](std::vector<T>& a){a[colN] = value;});
}

template <typename T>
void Matrix<T>::addRow(const std::vector<T>& row) {
	elements.push_back(row);
}

template <typename T>
void Matrix<T>::setMatchingRows(size_t rowN, T match, T set) {
	auto matchRow = elements[rowN];
	for (size_t i = 0; i < elements.size(); ++i) {
		for (size_t j = 0; j < elements[i].size(); ++j) {
			if (elements[i][j] == match &&
					elements[i][j] == matchRow[j]) {
				setRow(i, set);
				break;
			}
		}
	}
}

template <typename T>
void Matrix<T>::removeRow(size_t rowN) {
	if (rowN > elements.size()) {
		throw std::out_of_range("Attempted to remove non-existent row!");
	}
	elements.erase(elements.begin() + rowN);
}

template <typename T>
void Matrix<T>::removeCol(size_t colN) {
	std::for_each(elements.begin(), elements.end(),
		[&colN] (std::vector<T>& a) {
			if (colN > a.size()) {
				throw std::out_of_range("Attempted to remove non-existent column!");
			}
			a.erase(a.begin() + colN);
		});
}

template <typename T>
void Matrix<T>::removeMatchingRows(const std::vector<T>& row) {
	elements.erase(remove_if(elements.begin(), elements.end(),
			[&row](std::vector<T> r){return r == row;}), elements.end());
}

template <typename T>
bool Matrix<T>::isEmpty() const {
	// The presence of an empty row indicates a non-empty matrix!
	return elements.size() == 0;
}

template <typename T>
bool Matrix<T>::isEntirely(T value) const {
	for (auto v : elements) {
		if (std::find_if(v.begin(), v.end(),
				[&value](T t){return t != value;}) != v.end()) {
			return false;
		}
	}
	return true;
}

// TODO: Consider moving this out of Matrix; it's rather specialized...
template <typename T>
size_t Matrix<T>::validColumnWithFewest(T value, T invalid) const {
	int minCol = 0;
	int minCount = INT_MAX;
	for (int colN = 0; colN < numCols(); ++colN) {
		// Exclude columns consisting entirely of invalid
		if (std::find_if(elements.begin(), elements.end(),
				[&colN, &invalid](std::vector<T> t){return t[colN] != invalid;})
				== elements.end()) {
			continue;
		}
		// Count number of value in each column and keep track of minimum
		int count = count_if(elements.begin(), elements.end(),
				[&colN, &value](std::vector<T> t){return t[colN] == value;});
		if (count < minCount && count > 0) {
			minCount = count;
			minCol = colN;
		}
	}
	return minCol;
}

template <typename T>
bool Matrix<T>::inRow(T value, size_t rowN) const {
	const auto &begin = elements.at(rowN).begin();
	const auto &end = elements.at(rowN).end();
	return std::find(begin, end, value) != end;
}

template <typename T>
bool Matrix<T>::inCol(T value, size_t colN) const {
	return std::find_if(elements.begin(), elements.end(),
		[&colN, &value](std::vector<T> a){return a.at(colN) == value;}) != elements.end();
}

template <typename T>
size_t Matrix<T>::numRows() const {
	return elements.size();
}

template <typename T>
size_t Matrix<T>::numCols() const {
	return std::max_element(elements.begin(), elements.end(),
		[](std::vector<T> a, std::vector<T> b){return a.size() < b.size();})->size();
}

template <typename T>
const std::vector<T> Matrix<T>::operator[](size_t rowN) const {
	return elements.at(rowN);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
	for (auto row : m.elements) {
		for (auto col : row) {
			out << col;
		}
		out << std::endl;
	}
	return out;
}

