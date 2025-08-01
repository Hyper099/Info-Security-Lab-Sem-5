#include<bits/stdc++.h>
using namespace std;

int main(){
  int x = 5;
  int* y = &x;
  *y = 10;
  cout<<x<<endl;
  return 0;
}