#include <bits/stdc++.h>
using namespace std;

vector<int> generatePermutation(int size, int key) {
    vector<int> perm(size);
    iota(perm.begin(), perm.end(), 0);
    srand(key); 
    random_shuffle(perm.begin(), perm.end());
    return perm;
}

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

    vector<int> colPerm = generatePermutation(m, key);
    vector<char> shuffled(m);
    for (int col = 0; col < m; col++)
        shuffled[colPerm[col]] = plainText[col];

    string encrypted = "";
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            if (matrix[r][c] != '.') encrypted += shuffled[c];

    return encrypted;
}

string decrypt(string cipherText, int key) {
    int m = cipherText.length(), n = key;
    vector<vector<char>> matrix(n, vector<char>(m, '.'));

    int dir = 1, row = 0;
    for (int col = 0; col < m; col++) {
        matrix[row][col] = '*';
        row += dir;
        if (row == 0 || row == n - 1) dir *= -1;
    }

    int idx = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            if (matrix[r][c] == '*') matrix[r][c] = cipherText[idx++];

    string railText = "";
    dir = 1; row = 0;
    for (int col = 0; col < m; col++) {
        railText += matrix[row][col];
        row += dir;
        if (row == 0 || row == n - 1) dir *= -1;
    }

    vector<int> colPerm = generatePermutation(m, key);
    vector<char> unshuffled(m);
    for (int col = 0; col < m; col++)
        unshuffled[col] = railText[colPerm[col]];

    string decrypted = "";
    for (char c : unshuffled) decrypted += c;
    return decrypted;
}

int main() {
    string plainText = "wearediscoveringrailfencecipher";
    int key = 3;

    string encryptedText = encrypt(plainText, key);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText, key);
    cout << "Decrypted Text: " << decryptedText << endl;
}