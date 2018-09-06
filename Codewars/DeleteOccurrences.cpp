// Delete occurrences of an element if it occurs more than n times

#include <vector>
#include <map>

std::vector<int> deleteNth(std::vector<int> arr, int n)
{
	std::map<int, int> freq;
	std::vector<int> result;

	for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		if (freq.find(*it) == freq.end())
		{
			freq.insert(std::pair<int, int>(*it, 1));
			result.push_back(*it);
		}
		else
		{
			if (freq[*it] < n)
			{
				freq[*it]++;
				result.push_back(*it);
			}
		}
	}

	return result;
}