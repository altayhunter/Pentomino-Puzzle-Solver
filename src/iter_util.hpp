#pragma once
// https://stackoverflow.com/a/21510202/514165
#include <iterator>

template<typename It>
class Range
{
	It b, e;
public:
	Range(It b, It e) : b(b), e(e) {}
	It begin() const { return b; }
	It end() const { return e; }
};
 
// Allow iterable containers to be easily traversed in reverse order like so:
// vector<int> v;
// for (int i : reverse(v))
template<typename ORange, typename OIt = decltype(std::begin(std::declval<ORange>())), typename It = std::reverse_iterator<OIt>>
Range<It> reverse(ORange && originalRange) {
	return Range<It>(It(std::end(originalRange)), It(std::begin(originalRange)));
}
 
// Allow iterable containers to be easily traversed in vertical dimension like so:
// vector<int> v;
// for (int i : vertical(v))
template<typename ORange, typename OIt = decltype(std::declval<ORange>().vbegin()), typename It = OIt>
Range<It> vertical(ORange && originalRange) {
	return Range<It>(It(originalRange.vbegin()), It(originalRange.vend()));
}
