#include <vector>
#include <iostream>

using namespace std;

struct Solution
{
	~Solution() {}

	int Submarines_count = 4;
	int Destroyers_count = 3;
	int Cruisers_count = 2;
	int Battleship_count = 1;

	static const int Submarines_size = 1;
	static const int Destroyers_size = 2;
	static const int Cruisers_size = 3;
	static const int Battleship_size = 4;

	bool validate()
	{
		return (Battleship_count == 0 &&
			Cruisers_count == 0 &&
			Destroyers_count == 0 &&
			Submarines_count == 0);
	}

	bool check_result(int result)
	{
		if (result == Submarines_size)
		{
			Submarines_count--;
			return true;
		}

		if (result == Destroyers_size)
		{
			Destroyers_count--;
			return true;
		}

		if (result == Cruisers_size)
		{
			Cruisers_count--;
			return true;
		}

		if (result == Battleship_size)
		{
			Battleship_count--;
			return true;
		}

		return false;
	}
};

bool check_collisions_up(vector< vector<int> > &field, int x, int y)
{
	if (x - 1 >= 0 && field[x - 1][y] != 0) return false;
	if (x - 1 >= 0 && y - 1 >= 0 && field[x - 1][y - 1] != 0) return false;
	if (x - 1 >= 0 && y + 1 < 10 && field[x - 1][y + 1] != 0) return false;

	return true;
}

bool check_collisions_down(vector< vector<int> > &field, int x, int y)
{
	if (x + 1 < 10 && field[x + 1][y] != 0) return false;
	if (x + 1 < 10 && y - 1 >= 0 && field[x + 1][y - 1] != 0) return false;
	if (x + 1 < 10 && y + 1 < 10 && field[x + 1][y + 1] != 0) return false;

	return true;
}

bool check_collisions_left(vector< vector<int> > &field, int x, int y)
{
	if (y - 1 >= 0 && field[x][y - 1] != 0) return false;
	if (y - 1 >= 0 && x - 1 >= 0 && field[x - 1][y - 1] != 0) return false;
	if (y - 1 >= 0 && x + 1 < 10 && field[x + 1][y - 1] != 0) return false;

	return true;
}

bool check_collisions_right(vector< vector<int> > &field, int x, int y)
{
	if (y + 1 < 10 && field[x][y + 1] != 0) return false;
	if (y + 1 < 10 && x - 1 >= 0 && field[x - 1][y + 1] != 0) return false;
	if (y + 1 < 10 && x + 1 < 10 && field[x + 1][y + 1] != 0) return false;

	return true;
}

bool check_bounds(int x, int y)
{
	return (x >= 0 && x < 10 && y >= 0 && y < 10);
}

int check_right(vector< vector<int> > &field, int x, int y)
{
	if (!check_bounds(x, y))
	{
		return 0;
	}

	if (field[x][y] == 0)
	{
		return 0;
	}

	if (!check_collisions_up(field, x, y) || !check_collisions_down(field, x, y))
	{
		return -100;
	}

	field[x][y] = 0;
	return 1 + check_right(field, x, y + 1);
}

int check_down(vector< vector<int> > &field, int x, int y)
{
	if (!check_bounds(x, y))
	{
		return 0;
	}

	if (field[x][y] == 0)
	{
		return 0;
	}

	if (!check_collisions_left(field, x, y) || !check_collisions_right(field, x, y))
	{
		return -100;
	}

	field[x][y] = 0;
	return 1 + check_down(field, x + 1, y);
}

bool validate_battlefield(vector< vector<int> > field) {
	
	Solution solution;

	for(int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (field[x][y] == 1)
			{
				int size = 1;

				// exit
				if (x + 1 < 10 && y + 1 < 10 &&
					field[x + 1][y] == 1 && field[x][y + 1] == 1)
				{
					return false;
				}
				// go down
				if (x + 1 < 10 && field[x + 1][y] == 1)
				{
					size = check_down(field, x, y);
				}
				// go right
				if (y + 1 < 10 && field[x][y + 1] == 1)
				{
					size = check_right(field, x, y);
				}

				if (!solution.check_result(size))
				{
					return false;
				}
			}
		}
	}

	if (solution.validate())
	{
		return true;
	}

	return false;
}

/*int main()
{
	bool result = validate_battlefield(vector< vector<int> > {
			vector<int> {1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
			vector<int> {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
			vector<int> {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
			vector<int> {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
			vector<int> {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
			vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
			vector<int> {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
			vector<int> {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
			vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	});
	
	if (result)
	{
		cout << "Result OK" << endl;
	}
	else
	{
		cout << "Result not OK" << endl;
	}

	return 0;
}*/