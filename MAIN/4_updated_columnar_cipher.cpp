#include <bits/stdc++.h>
using namespace std;

vector<int> getKeyOrder(string key) {
    int n = key.size();
    vector<pair<char,int>> keyWithIndex;
    for (int i = 0; i < n; i++) keyWithIndex.push_back({key[i], i});
    sort(keyWithIndex.begin(), keyWithIndex.end());
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[keyWithIndex[i].second] = i;
    return order;
}

// pad the plaintext while its not multiple of n.
string padPlaintext(string plaintext, int blockSize, int seed) {
    srand(seed);
    while (plaintext.size() % blockSize != 0) {
        plaintext.push_back('A' + rand() % 26); // random padding
    }
    return plaintext;
}

string columnarEncrypt(string plaintext, string key) {
    int n = key.size();
    vector<int> colOrder = getKeyOrder(key);
    int seed = accumulate(key.begin(), key.end(), 0);
    plaintext = padPlaintext(plaintext, n, seed);

    int rows = plaintext.size() / n;
    vector<vector<char>> matrix(rows, vector<char>(n));
    int k = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = plaintext[k++];

    // Shuffle rows based on key-derived seed
    vector<int> rowOrder(rows);
    iota(rowOrder.begin(), rowOrder.end(), 0);
    srand(seed);
    random_shuffle(rowOrder.begin(), rowOrder.end());

    // Read columns in scrambled order
    string cipher = "";
    for (int col = 0; col < n; col++) {
        int realCol = find(colOrder.begin(), colOrder.end(), col) - colOrder.begin();
        for (int r = 0; r < rows; r++) cipher.push_back(matrix[rowOrder[r]][realCol]);
    }

    // Apply offset rotation based on key
    int offset = seed % cipher.size();
    rotate(cipher.begin(), cipher.begin() + offset, cipher.end());
    return cipher;
}

string columnarDecrypt(string ciphertext, string key) {
    int n = key.size();
    vector<int> colOrder = getKeyOrder(key);
    int seed = accumulate(key.begin(), key.end(), 0);

    // Undo rotation
    int offset = seed % ciphertext.size();
    rotate(ciphertext.begin(), ciphertext.end() - offset, ciphertext.end());

    int rows = ciphertext.size() / n;
    vector<vector<char>> matrix(rows, vector<char>(n));
    vector<int> rowOrder(rows);
    iota(rowOrder.begin(), rowOrder.end(), 0);
    srand(seed);
    random_shuffle(rowOrder.begin(), rowOrder.end());

    // Place ciphertext back into columns
    int k = 0;
    for (int col = 0; col < n; col++) {
        int realCol = find(colOrder.begin(), colOrder.end(), col) - colOrder.begin();
        for (int r = 0; r < rows; r++)
            matrix[rowOrder[r]][realCol] = ciphertext[k++];
    }

    // Read row-wise
    string plaintext = "";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < n; j++)
            plaintext.push_back(matrix[i][j]);

    return plaintext;
}

int main() {
    string plaintext = "WEAREDISCOVERINGCOLUMNAR";
    string key = "ZEBRAS";

    string cipher = columnarEncrypt(plaintext, key);
    cout << "Encrypted: " << cipher << endl;

    string decrypted = columnarDecrypt(cipher, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}