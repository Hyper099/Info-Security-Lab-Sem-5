#include <bits/stdc++.h>
using namespace std;

string delete_char_cpp(string s, char ch) {
	string new_str = "";
	for (char c : s) {
		if (c != ch) {
			new_str += c;
		}
	}
	return new_str;
}

pair<array<array<char, 5>, 5>, unordered_map<char, pair<int,int>>> buildMatrix(const string& key) {
	array<array<char, 5>, 5> matrix{};
	char skipChar = 'j';
	string ap = "abcdefghijklmnopqrstuvwxyz";
	string alphabets = delete_char_cpp(ap, skipChar);

	unordered_map<char, pair<int,int>> used;
	int n = key.length(), k = 0, a = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (k < n) {
				while (k < n && used.find(key[k]) != used.end()) k++;
				if (k < n) {
					matrix[i][j] = key[k];
					used[key[k]] = {i,j};
					k++;
				}
			} else {
				while (a < alphabets.size() && used.find(alphabets[a]) != used.end()) a++;
				if (a < alphabets.size()) {
					matrix[i][j] = alphabets[a];
					used[alphabets[a]] = {i,j};
					a++;
				}
			}
		}
	}
	return {matrix, used};
}

vector<string> preprocessPlainText(string& plainText) {
	char skipChar = 'j';
	for (char &ch: plainText) {
		if (ch == skipChar) {
			ch = 'i'; // replace j with i
		}
	}

	vector<string> cleanedText;
	int len = plainText.length() - (plainText.length() % 2);
	for (int i = 0 ; i < len; i+=2) {
		string temp = "";
		if (plainText[i] != plainText[i + 1]) {
			temp += plainText[i];
			temp += plainText[i+1];
			cleanedText.push_back(temp);
		} else {
			temp += plainText[i];
			temp += 'z';
			cleanedText.push_back(temp);

			temp = "";
			temp += plainText[i+1];
			temp += 'z';
			cleanedText.push_back(temp);
		}
	}
	if (plainText.length() % 2) {
		string temp = "";
		temp += plainText[len];
		temp += 'z';
		cleanedText.push_back(temp);
	}
	return cleanedText;
}

string encrypt(string& plainText, const string& key) {
	auto [matrix, used] = buildMatrix(key);
	vector<string> cleanedText = preprocessPlainText(plainText);

	string cipherText = "";
	for (const auto &x: cleanedText) {
		pair<int,int> l1 = used[x[0]];
		pair<int,int> l2 = used[x[1]];

		if (l1.second == l2.second) { 
			cipherText += matrix[(l1.first + 1) % 5][l1.second];
			cipherText += matrix[(l2.first + 1) % 5][l2.second];
		} else if (l1.first == l2.first) { 
			cipherText += matrix[l1.first][(l1.second + 1) % 5];
			cipherText += matrix[l1.first][(l2.second + 1) % 5];
		} else { 
			cipherText += matrix[l1.first][l2.second];
			cipherText += matrix[l2.first][l1.second];
		}
	}
	return cipherText;
}

string decrypt(string& cipherText, const string& key) {
	auto [matrix, used] = buildMatrix(key);
	string plainText = "";

	for (int i = 0; i < cipherText.length(); i += 2) {
		pair<int,int> l1 = used[cipherText[i]];
		pair<int,int> l2 = used[cipherText[i+1]];

		if (l1.second == l2.second) { 
			plainText += matrix[(l1.first - 1 + 5) % 5][l1.second];
			plainText += matrix[(l2.first - 1 + 5) % 5][l2.second];
		} else if (l1.first == l2.first) { 
			plainText += matrix[l1.first][(l1.second - 1 + 5) % 5];
			plainText += matrix[l1.first][(l2.second - 1 + 5) % 5];
		} else { 
			plainText += matrix[l1.first][l2.second];
			plainText += matrix[l2.first][l1.second];
		}
	}
	return plainText;
}

int main() {
	string plainText;
	string key;

	cout << "Enter Message : ";
	getline(cin, plainText);

	cout << "Enter Key: ";
	cin >> key;

	string cipherText = encrypt(plainText, key);
	cout << "Encrypted: " << cipherText << endl;

	string decryptedText = decrypt(cipherText, key);
	cout << "Decrypted: " << decryptedText << endl;

	return 0;
}