#include <algorithm>
#include <iostream>
#include <string>

#define N 8

using namespace std;

int hist[N][26];

int main() {
  string msg;
  while(getline(cin, msg)) {
    for(int i = 0; i < N; i++)
      hist[i][msg[i] - 'a']++;
  }

  string decoded1(N, ' '), decoded2(N, ' ');
  for(int i = 0; i < N; i++) {
    decoded1[i] = 'a' + max_element(hist[i], hist[i] + 26) - hist[i];
    decoded2[i] = 'a' + min_element(hist[i], hist[i] + 26) - hist[i];
  }
  cout << decoded1 << endl;
  cout << decoded2 << endl;
  return 0;
}
