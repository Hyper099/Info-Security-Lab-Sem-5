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

string caesarShift(const string& text, int shift) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = 'a';
            res += char((c - base + shift + 26) % 26 + base);
        } else res += c;
    }
    return res;
}

pair<array<array<char, 5>, 5>, unordered_map<char, pair<int,int>>> buildMatrix(const string& key) {
    array<array<char, 5>, 5> matrix{};

    string vowels = "aeiou";
    char skipChar = vowels[key.length() % vowels.size()];

    string ap = "abcdefghijklmnopqrstuvwxyz";
    string alphabets = delete_char_cpp(ap, skipChar);

    unordered_map<char, pair<int,int>> used;
    int n = key.length(), k = 0, a = 0;

    // XOR with key length 
    string transformedKey = key;
    for (char &c : transformedKey) {
        c = ((c - 'a' + key.length()) % 26) + 'a';
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (k < n) {
                while (k < n && used.find(transformedKey[k]) != used.end()) k++;
                if (k < n) {
                    matrix[i][j] = transformedKey[k];
                    used[transformedKey[k]] = {i,j};
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
    
    for (char &ch: plainText) {
        if (!isalpha(ch)) continue;
        ch = tolower(ch);
    }

    vector<string> cleanedText;
    string fillers = "xyz"; 
    int len = plainText.length() - (plainText.length() % 2);
    for (int i = 0 ; i < len; i+=2) {
        string temp = "";
        if (plainText[i] != plainText[i + 1]) {
            temp += plainText[i];
            temp += plainText[i+1];
            cleanedText.push_back(temp);
        } else {
            temp += plainText[i];
            temp += fillers[(i/2) % fillers.size()];
            cleanedText.push_back(temp);

            temp = "";
            temp += plainText[i+1];
            temp += fillers[(i/2+1) % fillers.size()];
            cleanedText.push_back(temp);
        }
    }
    if (plainText.length() % 2) {
        string temp = "";
        temp += plainText[len];
        temp += fillers[(len/2) % fillers.size()];
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

    cipherText = caesarShift(cipherText, key.length() % 26);

    return cipherText;
}

string decrypt(string& cipherText, const string& key) {
    
    cipherText = caesarShift(cipherText, -(key.length() % 26));

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