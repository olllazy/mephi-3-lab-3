#pragma once
#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H 
#include <iostream> 
#include <fstream>
#include <string>
//#include "iss.h"

template <typename F, typename S>
struct Pair {

	F first = 0;
	S second = 0;

	bool operator==(Pair<F, S>& other) const {
		return (this->first == other.first) && (this->second == other.second);
	}
	bool operator!=(Pair<F, S>& other) const {
		return (this->first != other.first) || (this->second != other.second);
	}

	//F getKey() {
	//	return key;
	//}
	/*bool operator>(KeyValuePair<F, S>& p2) const {
		return this->first > p2.key;
	}
	bool operator<(KeyValuePair<F, S>& p2) const {
		return this->key < p2.key;
	}*/

	//friend std::ostream& operator<<(std::ostream& out, const KeyValuePair<V,K>& p2);
};

//class AlphabetIndex {
//private:
//	std::string text;
//	ISortedSequence<KeyValuePair<int, std::string>>* alind;
//public:
//	AlphabetIndex() { text = ""; alind = nullptr; }
//};


#endif // KEYVALUEPAIR_H


