#include <bits/stdc++.h>
using namespace std;

char vigenereTable[26][26];

void initVigenereTable() {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            vigenereTable[i][j] = 'A' + (i + j) % 26;
        }
    }
}

string generateKey(const string &text, const string &key) {
    string newKey = key;
    while (newKey.size() < text.size())
        newKey += key;
    return newKey.substr(0, text.size());
}

string vigenereEncrypt(const string &plaintext, const string &key) {
    string newKey = generateKey(plaintext, key);
    string cipher = "";
    int dynamicShift = 0; // Changes after each character

    for (int i = 0; i < plaintext.size(); i++) {
        char p = toupper(plaintext[i]);
        char k = toupper(newKey[i]);

        if (isalpha(p)) {
            int row = (k - 'A' + dynamicShift + i) % 26; 
            int col = p - 'A';
            char enc = vigenereTable[row][col];
            cipher += isupper(plaintext[i]) ? enc : tolower(enc);

            // Dynamically update the shift according to the encrypted character.
            dynamicShift = (dynamicShift + (enc - 'A')) % 26;
        } else {
            cipher += plaintext[i];
        }
    }
    return cipher;
}

// Decrypt with variation
string vigenereDecrypt(const string &ciphertext, const string &key) {
    string newKey = generateKey(ciphertext, key);
    string plain = "";
    int dynamicShift = 0;

    for (int i = 0; i < ciphertext.size(); i++) {
        char c = toupper(ciphertext[i]);
        char k = toupper(newKey[i]);

        if (isalpha(c)) {
            int row = (k - 'A' + dynamicShift + i) % 26;

            // Find the column in the table
            int col = 0;
            while (col < 26 && vigenereTable[row][col] != c) col++;
            char dec = 'A' + col;
            plain += isupper(ciphertext[i]) ? dec : tolower(dec);

            dynamicShift = (dynamicShift + (c - 'A')) % 26;
        } else {
            plain += ciphertext[i];
        }
    }
    return plain;
}

int main() {
    initVigenereTable();

    string plaintext = "WEAREDISCOVERINGVIGENERE";
    string key = "KEY";

    string encrypted = vigenereEncrypt(plaintext, key);
    cout << "Encrypted: " << encrypted << endl;

    string decrypted = vigenereDecrypt(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}