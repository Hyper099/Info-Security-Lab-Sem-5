#include <iostream>
#include <string>
using namespace std;

void encrypt(string &cipherText, const string &plainText, int key)
{
   cipherText = "";
   for (char ch : plainText)
   {
      if (ch >= 'a' && ch <= 'z')
         cipherText += char((ch - 'a' + key) % 26 + 'a');
      else if (ch >= 'A' && ch <= 'Z')
         cipherText += char((ch - 'A' + key) % 26 + 'a');
      else if (ch >= '0' && ch <= '9')
         cipherText += char((ch - '0' + key) % 10 + '0');
      else
         cipherText += ch;
   }
}

void decrypt(string &plainText, const string &cipherText, int key)
{
   plainText = "";
   for (char ch : cipherText)
   {
      if (ch >= 'a' && ch <= 'z')
         plainText += char((ch - 'a' - key + 26) % 26 + 'a');
      else if (ch >= 'A' && ch <= 'Z')
         plainText += char((ch - 'A' - key + 26) % 26 + 'a');
      else if (ch >= '0' && ch <= '9')
         plainText += char((ch - '0' - key + 10) % 10 + '0');
      else
         plainText += ch;
   }
}

int main()
{
   string plainText, cipherText, decryptedText;
   int key;

   cout << "Enter your message: ";
   getline(cin, plainText);

   cout << "Enter the shift value: ";
   cin >> key;

   encrypt(cipherText, plainText, key);
   cout << "Encrypted message: " << cipherText << endl;

   decrypt(decryptedText, cipherText, key);
   cout << "Decrypted message: " << decryptedText << endl;

   return 0;
}
