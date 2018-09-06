#include <string>
#include <algorithm> 

bool smaller(char i) { return i < '5'; }
bool greater(char i) { return i >= '5'; }

std::string fakeBin(std::string str) {

	std::replace_if(str.begin(), str.end(), smaller, '0');
	std::replace_if(str.begin(), str.end(), greater, '1');

	return str;
}