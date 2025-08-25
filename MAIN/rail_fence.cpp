#include <bits/stdc++.h>
using namespace std;


string encrypt(string plainText, int key){
    int n = key, m = plainText.length();
    vector<vector<char>> matrix (n, vector<char>(m,'.'));

    int cnt = 0, flag = 0, k = 0, i = 0, j = 0;
    while( j < m){
        matrix[i][j] = plainText[j]; cnt++;
        if(cnt >= key){
            flag = !flag;
            cnt = 1;
        }
        
        if(!flag){
            i++; 
        }else{
            i--; 
        }
        j++;
    }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    string encryptedText = "";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(matrix[i][j] == '.')continue;
            encryptedText += matrix[i][j];
        }
    }
    return encryptedText;
}

string decrypt(string cipherText, int key){
    int m = cipherText.length(), n = key; 
    vector<vector<char>> matrix (n, vector<char>(m,'.'));

     int mxSkip = 
    
}



int main(){
    string plainText = "wearediscoveringrailfencecipher";
    int key = 3;

    string encryptedText = encrypt(plainText, key);
    cout << "Encrypted Text : " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText, key);
    cout << "Decrypted Text : " << decryptedText << endl;
}