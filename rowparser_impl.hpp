#pragma once

template <typename T>
RowParser<T>::RowParser(std::function<T(char)> f) :
	converter(f) {
}

template <typename T>
std::vector<T> RowParser<T>::getRow() const {
	return row;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const RowParser<T>& rp) {
	for (auto t : rp.row) {
		out << t;
	}
	out << std::endl;
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, RowParser<T>& rp) {
	rp.row.clear();
	char c;
	while (in.get(c)) {
		if (c == '0' || c == '1') {
			rp.row.push_back(rp.converter(c));
		// Stop parsing after two consecutive linefeeds
		} else if (c == '\n' && in.peek() == '\n') {
			in.get(c);
			break;
		}
	}
	return in;
}
