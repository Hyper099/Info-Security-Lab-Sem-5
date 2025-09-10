#include <bits/stdc++.h>
using namespace std;

string encrypt(string plainText, int key) {
    int n = key, m = plainText.length();
    vector<vector<char>> matrix(n, vector<char>(m, '.'));

    int cnt = 0, flag = 0, i = 0, j = 0;
    while (j < m) {
        matrix[i][j] = plainText[j];
        cnt++;
        if (cnt >= key) {
            flag = !flag;
            cnt = 1;
        }

        if (!flag) i++;
        else i--;
        j++;
    }

    string encryptedText = "";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] != '.')
                encryptedText += matrix[i][j];
        }
    }
    return encryptedText;
}

string decrypt(string cipherText, int key) {
    int m = cipherText.length(), n = key;
    vector<vector<char>> matrix(n, vector<char>(m, '.'));

    // Step 1: Mark positions where characters will go
    int cnt = 0, flag = 0, i = 0, j = 0;
    while (j < m) {
        matrix[i][j] = '*'; // mark
        cnt++;
        if (cnt >= key) {
            flag = !flag;
            cnt = 1;
        }

        if (!flag) i++;
        else i--;
        j++;
    }

    // Step 2: Fill the marked positions with ciphertext characters
    int index = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (matrix[r][c] == '*' && index < m) {
                matrix[r][c] = cipherText[index++];
            }
        }
    }

    // Step 3: Read characters in zig-zag order
    string decryptedText = "";
    cnt = 0; flag = 0; i = 0; j = 0;
    while (j < m) {
        decryptedText += matrix[i][j];
        cnt++;
        if (cnt >= key) {
            flag = !flag;
            cnt = 1;
        }

        if (!flag) i++;
        else i--;
        j++;
    }

    return decryptedText;
}

int main() {
    string plainText = "wearediscoveringrailfencecipher";
    int key = 3;

    string encryptedText = encrypt(plainText, key);
    cout << "Encrypted Text : " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText, key);
    cout << "Decrypted Text : " << decryptedText << endl;

    return 0;
}