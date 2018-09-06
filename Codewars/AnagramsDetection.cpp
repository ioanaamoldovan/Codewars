// Anagrams detection

#include <string>
#include <algorithm>  

bool isAnagram(std::string test, std::string original) {

	std::transform(test.begin(), test.end(), test.begin(), ::tolower);
	std::sort(test.begin(), test.end());

	std::transform(original.begin(), original.end(), original.begin(), ::tolower);
	std::sort(original.begin(), original.end());

	return test == original;
}