#include <bits/stdc++.h>
using namespace std;

vector<int> getKeyOrder(string key) {
   int n = key.size();
   vector<pair<char,int>> keyWithIndex;
   for(int i=0; i<n; i++)
      keyWithIndex.push_back({key[i], i});

   sort(keyWithIndex.begin(), keyWithIndex.end());

   vector<int> order(n);
   for(int i=0; i<n; i++)
      order[keyWithIndex[i].second] = i;

   return order;
}


string columnarEncrypt(string plaintext, string key) {
   int n = key.size();
   vector<int> order = getKeyOrder(key);

   plaintext.erase(remove(plaintext.begin(), plaintext.end(), ' '), plaintext.end());

   // Fill into matrix row-wise
   int rows = ceil((double)plaintext.size() / n);
   vector<vector<char>> matrix(rows, vector<char>(n, 'X')); // pad with 'X'

   int k = 0;
   for(int i=0; i<rows; i++) {
      for(int j=0; j<n; j++) {
         if(k < plaintext.size())
               matrix[i][j] = plaintext[k++];
      }
   }

   // Read column by column in key order
   string cipher = "";
   for(int col=0; col<n; col++) {
      int currCol = find(order.begin(), order.end(), col) - order.begin();
      for(int row=0; row<rows; row++)
         cipher.push_back(matrix[row][currCol]);
   }

   return cipher;
}

// Decryption
string columnarDecrypt(string ciphertext, string key) {
   int n = key.size();
   vector<int> order = getKeyOrder(key);

   int rows = ceil((double)ciphertext.size() / n);
   vector<vector<char>> matrix(rows, vector<char>(n, 'X'));

   // Fill column by column according to order
   int k = 0;
   for(int col=0; col<n; col++) {
      int currCol = find(order.begin(), order.end(), col) - order.begin();
      for(int row=0; row<rows; row++) {
         if(k < ciphertext.size())
               matrix[row][currCol] = ciphertext[k++];
      }
   }

   // Read row by row to get plaintext
   string plaintext = "";
   for(int i=0; i<rows; i++) {
      for(int j=0; j<n; j++) {
         if(matrix[i][j] != 'X')
               plaintext.push_back(matrix[i][j]);
      }
   }

   return plaintext;
}

// Main
int main() {
   string plaintext = "WEAREDISCOVERINGCOLUMNAR";
   string key = "ZEBRAS";

   string cipher = columnarEncrypt(plaintext, key);
   cout << "Encrypted: " << cipher << endl;

   string decrypted = columnarDecrypt(cipher, key);
   cout << "Decrypted: " << decrypted << endl;

   return 0;
}