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

string encrypt(string& plainText, const string& key){
	char matrix[5][5], n = key.length(), k = 0, a = 0;
	
	char skipChar = 'j';
	string ap = "abcdefghijklmnopqrstuvwxyz";
	string alphabets = delete_char_cpp(ap, skipChar);
	
	unordered_map<char, pair<int,int>> used;

	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(k < n){
				while(used.find(key[k]) != used.end()) k++;
				matrix[i][j] = key[k];
				used[key[k]] = {i,j};
				k++;
			}else{
				while(used.find(alphabets[a]) != used.end()) a++;
				matrix[i][j] = alphabets[a];
				used[alphabets[a]] = {i,j};
				a++;
			}
		}
	}

	// Cleaning PlainText;
	// 1. Cleaning skipped character from plainText
	for(char &ch: plainText){
		if(ch == skipChar){
			ch = char((skipChar - 'a') - 1 + 'a');
		}
	}
	
	vector<string> cleanedText;
	int len = plainText.length() - (plainText.length() % 2);
	for(int i = 0 ; i < len; i+=2){
		string temp = "";
		// case 1 : normal 
		if(plainText[i] != plainText[i + 1]){
			temp += plainText[i];
			temp += plainText[i+1];
			cleanedText.push_back(temp);
		}
		// case 2: 2 same characters.
		else if(plainText[i] == plainText[i+1]){
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

	string cipherText = "";
	for(const auto &x: cleanedText){
		pair<int,int> l1 = used[x[0]];
		pair<int,int> l2 = used[x[1]];

		// parse column
		if(l1.second == l2.second){
			cipherText += matrix[(((l1.first - 1) + 5) % 5)][l1.second];
			cipherText += matrix[(((l2.first - 1) + 5) % 5)][l2.second];

		}else if(l1.first == l2.first){
			cipherText += matrix[l1.first][((l1.second + 1) + 5) % 5];
			cipherText += matrix[l1.first][((l2.second + 1) + 5) % 5];
		}
		else{
			cipherText += matrix[l1.first][l2.second];
			cipherText += matrix[l2.first][l1.second];
		}
	} 
	return cipherText;
}



int main(){
	string plainText;
	string key;
	
	cout << "Enter Message : ";
	getline(cin, plainText);

	cout << "Enter Key: ";
	cin >> key;

	string cipherText = encrypt(plainText, key);
	cout << cipherText << endl;

	return 0;
}