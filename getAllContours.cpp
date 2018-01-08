#include <bits/stdc++.h>

using namespace std;

int main(){
  string com;
  for(int i=0;i<72;i++){
    com = "./getContour "+to_string(i);
    system(com.c_str());
  }
  return 0;
}
