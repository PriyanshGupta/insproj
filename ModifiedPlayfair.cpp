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

void removeSpaces(string &s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
			s.erase(s.begin() + i);
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

string encrypt(string plaintext, vector<vector<char>> matrix, unordered_map<char, pair<int, int>> valueMap)
{
	for (int i = 0; i < plaintext.length(); i += 2)
	{
		if (plaintext[i] == plaintext[i + 1])
			plaintext.insert(i + 1, "x");
	}

	if (plaintext.length() % 2 != 0)
		plaintext += "x";

	string ans = "";

	for (int i = 0; i < plaintext.length(); i += 2)
	{
		int row1 = valueMap[plaintext[i]].first;
		int col1 = valueMap[plaintext[i]].second;
		int row2 = valueMap[plaintext[i + 1]].first;
		int col2 = valueMap[plaintext[i + 1]].second;

		if (row1 == row2)
		{
			ans += matrix[row1][(col1 + 1) % 9];
			ans += matrix[row1][(col2 + 1) % 9];
		}
		else if (col1 == col2)
		{
			ans += matrix[(row1 + 1) % 9][col1];
			ans += matrix[(row2 + 1) % 9][col1];
		}
		else
		{
			ans += matrix[row1][col2];
			ans += matrix[row2][col1];
		}
	}

	return ans;
}

string decrypt(string ciphertext, vector<vector<char>> matrix, unordered_map<char, pair<int, int>> valueMap)
{
	string ans = "";

	for (int i = 0; i < ciphertext.length(); i += 2)
	{
		int row1 = valueMap[ciphertext[i]].first;
		int col1 = valueMap[ciphertext[i]].second;
		int row2 = valueMap[ciphertext[i + 1]].first;
		int col2 = valueMap[ciphertext[i + 1]].second;

		if (row1 == row2)
		{
			ans += matrix[row1][(col1 + 8) % 9];
			ans += matrix[row1][(col2 + 8) % 9];
		}
		else if (col1 == col2)
		{
			ans += matrix[(row1 + 8) % 9][col1];
			ans += matrix[(row2 + 8) % 9][col1];
		}
		else
		{
			ans += matrix[row1][col2];
			ans += matrix[row2][col1];
		}
	}

	return ans;
}

int main()
{
	getDefaultMap();
	string key;
	string plaintext;

	cout << "Enter Key: ";
	getline(cin, key);
	cout << "Enter Plaintext: ";
	getline(cin, plaintext);

	removeSpaces(key);
	removeSpaces(plaintext);

	unordered_map<char, pair<int, int>> valueMap1;
	vector<vector<char>> matrix1 = make_matrix(key, valueMap1);
	cout << "\nFirst Matrix:" << endl;
	printMatrix(matrix1);

	string ciphertext1 = encrypt(plaintext, matrix1, valueMap1);
	cout << "\nText after first encyption: " << ciphertext1 << endl << endl;

	string key2 = mutate(key);
	cout << "New Key: " << key2 << endl;

	unordered_map<char, pair<int, int>> valueMap2;
	vector<vector<char>> matrix2 = make_matrix(key2, valueMap2);
	cout << "\nSecond Matrix:" << endl;
	printMatrix(matrix2);

	string ciphertext2 = encrypt(ciphertext1, matrix2, valueMap2);
	cout << "\nText after second encyption: " << ciphertext2 << endl << endl;

	cout << "Encrypted Text: " << ciphertext2 << endl;
	cout << "Final deciphered Text: " << decrypt(decrypt(ciphertext2, matrix2, valueMap2), matrix1, valueMap1) << endl;

}
