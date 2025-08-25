#include <iostream>
#include <string>
using namespace std;

void encrypt(string &cipherText, const string &plainText, int key1, int key2) {
    cipherText = "";
    for (int i = 0; i < plainText.size(); i++) {
        char ch = plainText[i];
        int key = (i % 2 == 0) ? key1 : key2; 
        if (ch >= 'a' && ch <= 'z')
            cipherText += char((ch - 'a' + key) % 26 + 'a');
        else if (ch >= 'A' && ch <= 'Z')
            cipherText += char((ch - 'A' + key) % 26 + 'A');
        else
            cipherText += ch;
    }
}

void decrypt(string &plainText, const string &cipherText, int key1, int key2) {
    plainText = "";
    for (int i = 0; i < cipherText.size(); i++) {
        char ch = cipherText[i];
        int key = (i % 2 == 0) ? key1 : key2; 
        if (ch >= 'a' && ch <= 'z')
            plainText += char((ch - 'a' - key + 26) % 26 + 'a');
        else if (ch >= 'A' && ch <= 'Z')
            plainText += char((ch - 'A' - key + 26) % 26 + 'A');
        else
            plainText += ch;
    }
}

int main() {
    string plainText, cipherText, decryptedText;
    int key1, key2;

    cout << "Enter your message: ";
    getline(cin, plainText);

    cout << "Enter first key: ";
    cin >> key1;

    cout << "Enter second key: ";
    cin >> key2;   

    encrypt(cipherText, plainText, key1, key2);
    cout << "Encrypted message: " << cipherText << endl;

    decrypt(decryptedText, cipherText, key1, key2);
    cout << "Decrypted message: " << decryptedText << endl;

    return 0;
}