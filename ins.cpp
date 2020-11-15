#include <bits/stdc++.h>
using namespace std;

const vector<vector<char>> defaultMatrix
{	{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'},
	{'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
	{'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A'},
	{'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'},
	{'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S'},
	{'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2'},
	{'3', '4', '5', '6', '7', '8', '9', '0', '?'},
	{'.', '-', '@', '!', ':', ';', '+', '_', '*'},
	{'%', '/', '(', ')', '<', '>', '=', '&', '|'}
};

unordered_map<char, pair<int, int>> defaultMap;

void getDefaultMap() {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			defaultMap[defaultMatrix[i][j]] = {i, j};
		}
	}
}

string mutate(string key)
{
	int len = key.length();
	string newKey = key;
	for (int i = 0; i <= len / 2; i += 2)
	{
		char temp = newKey[i];
		newKey[i] = newKey[len - i - 1];
		newKey[len - i - 1] = temp;
	}
	return newKey;
}

vector<vector<char>> make_matrix(string key, unordered_map<char, pair<int, int>> &m)
{
	vector<vector<char>> c;
	for (int i = 0; i < 9; i++)
	{
		vector<char> v;
		for (int j = 0; j < 9; j++)
		{
			v.push_back('\0');
		}
		c.push_back(v);
	}

	bool **visited = new bool*[9];
	for (int i = 0; i < 9; i++)
	{
		visited[i] = new bool[9];
		for (int j = 0; j < 9; j++)
		{
			visited[i][j] = false;
		}
	}

	int keyLen = key.length();
	int pos = 0;
	for (int i = 0; i < keyLen; i++)
	{
		if (!visited[defaultMap[key[i]].first][defaultMap[key[i]].second])
		{
			int row = pos / 9;
			int col = pos % 9;
			c[row][col] = key[i];
			visited[defaultMap[key[i]].first][defaultMap[key[i]].second] = true;
			m[c[row][col]] = {row, col};
			pos++;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (!visited[i][j])
			{
				int row = pos / 9;
				int col = pos % 9;
				c[row][col] = defaultMatrix[i][j];
				visited[i][j] = true;
				m[c[row][col]] = {row, col};
				pos++;
			}
		}
	}

	return c;
}

void printMatrix(vector<vector<char>> m)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

void encrypt(string plaintext, string key)
{
	unordered_map<char, pair<int, int>> map1;
	vector<vector<char>> m1 = make_matrix(key, map1);
	printMatrix(m1);
	cout << defaultMap['H'].first << " " << defaultMap['H'].second << endl;
	cout << map1['H'].first << " " << map1['H'].second << endl;

}

int main()
{
	getDefaultMap();
	string key = "Hello";
	encrypt("", key);
}