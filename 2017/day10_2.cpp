#include <cstdio>
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>

#define N 256
#define ROUNDS 64

using namespace std;

int list[N];
vector<int> lenghts;

int main() {
  for(int i = 0; i < N; i++)
    list[i] = i;

  char ch;
  while(scanf("%c", &ch) > 0) {
    cerr << (int) ch << endl;
    lenghts.push_back(ch);
  }
  lenghts.insert(lenghts.end(), { 17, 31, 73, 47, 23 });

  int curr = 0, skip = 0;
  for(int k = 0; k < ROUNDS; k++) {
    for(int len : lenghts) {
      for(int i = 0; i < len / 2; i++) {
        swap(list[(curr + i) % N], list[(curr + len - i - 1) % N]);
      }
      curr = (curr + len + skip++) % N;
    }
  }

  for(int i = 0; i < N; i += 16) {
    int elem = 0;
    for(int j = 0; j < 16 && i + j < N; j++) {
      elem ^= list[i + j];
    }
    cout << setw(2) << setfill('0') << hex << elem;
  }
  cout << endl;
  return 0;
}
