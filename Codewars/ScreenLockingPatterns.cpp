#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct nodes {
	char name;
	bool visited;
	char other;
};

map<char, int> paths;
map<char, int> visited;

map<char, vector<nodes>> graph =
{
	{ 'A',{ { 'B', true,   0 },{ 'C', false, 'B' },{ 'D', true,   0 },{ 'E', true,   0 },{ 'F', true,   0 },{ 'G', false, 'D' },{ 'H', true,   0 },{ 'I', false, 'E' } } },
	{ 'B',{ { 'A', true,   0 },{ 'C', true,   0 },{ 'D', true,   0 },{ 'E', true,   0 },{ 'F', true,   0 },{ 'G', true,   0 },{ 'H', false, 'E' },{ 'I', true,   0 } } },
	{ 'C',{ { 'A', false, 'B' },{ 'B', true,   0 },{ 'D', true,   0 },{ 'E', true,   0 },{ 'F', true,   0 },{ 'G', false, 'E' },{ 'H', true,   0 },{ 'I', false, 'F' } } },
	{ 'D',{ { 'A', true,   0 },{ 'B', true,   0 },{ 'C', true,   0 },{ 'E', true,   0 },{ 'F', false, 'E' },{ 'G', true,   0 },{ 'H', true,   0 },{ 'I', true,   0 } } },
	{ 'E',{ { 'A', true,   0 },{ 'B', true,   0 },{ 'C', true,   0 },{ 'D', true,   0 },{ 'F', true,   0 },{ 'G', true,   0 },{ 'H', true,   0 },{ 'I', true,   0 } } },
	{ 'F',{ { 'A', true,   0 },{ 'B', true,   0 },{ 'C', true,   0 },{ 'D', false, 'E' },{ 'E', true,   0 },{ 'G', true,   0 },{ 'H', true,   0 },{ 'I', true,   0 } } },
	{ 'G',{ { 'A', false, 'D' },{ 'B', true,   0 },{ 'C', false, 'E' },{ 'D', true,   0 },{ 'E', true,   0 },{ 'F', true,   0 },{ 'H', true,   0 },{ 'I', false, 'H' } } },
	{ 'H',{ { 'A', true,   0 },{ 'B', false, 'E' },{ 'C', true,   0 },{ 'D', true,   0 },{ 'E', true,   0 },{ 'F', true,   0 },{ 'G', true,   0 },{ 'I', true,   0 } } },
	{ 'I',{ { 'A', false, 'E' },{ 'B', true,   0 },{ 'C', false, 'F' },{ 'D', true,   0 },{ 'E', true,   0 },{ 'F', true,   0 },{ 'G', false, 'H' },{ 'H', true,   0 } } }
};

void solve(char sourceNode, char currentNode, unsigned short length, unsigned int& count)
{
	if (paths[currentNode] == length)
	{
		count++;
	}
	else
	{
		for (auto neighbor : graph[currentNode])
		{
			if ((neighbor.visited == true && visited[neighbor.name] == 0) ||
				(neighbor.visited == false && visited[neighbor.other] != 0 && visited[neighbor.name] == 0))
			{
				paths[neighbor.name] = paths[currentNode] + 1;
				visited[neighbor.name] += 1;

				solve(sourceNode, neighbor.name, length, count);

				paths[neighbor.name] = paths[currentNode] + 1;
				visited[neighbor.name] -= 1;
			}
		}
	}
}

unsigned int countPatternsFrom(char firstDot, unsigned short length) {

	if (length == 0) return 0;
	if (length == 1) return 1;
	if (length > 9) return 0;

	unsigned int count = 0;
	paths.clear();
	visited.clear();
	paths[firstDot] = 1;
	visited[firstDot] = 1;
	solve(firstDot, firstDot, length, count);
	return count;
}

/*int main()
{
	cout << countPatternsFrom('A', 0) << endl;
	cout << countPatternsFrom('A', 10) << endl;
	cout << countPatternsFrom('B', 1) << endl;
	cout << countPatternsFrom('C', 2) << endl;
	cout << countPatternsFrom('D', 3) << endl;
	cout << countPatternsFrom('E', 4) << endl;
	cout << countPatternsFrom('E', 8) << endl;
	return 0;
}*/