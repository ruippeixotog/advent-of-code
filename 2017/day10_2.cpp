#include <cstdio>
#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>

#define N 256
#define ROUNDS 64

using namespace std;

vector<int> knotHash(string lenghts) {
  lenghts.insert(lenghts.end(), { 17, 31, 73, 47, 23 });

  int list[N];
  for(int i = 0; i < N; i++)
    list[i] = i;

  int curr = 0, skip = 0;
  for(int k = 0; k < ROUNDS; k++) {
    for(int len : lenghts) {
      for(int i = 0; i < len / 2; i++) {
        swap(list[(curr + i) % N], list[(curr + len - i - 1) % N]);
      }
      curr = (curr + len + skip++) % N;
    }
  }

  vector<int> hash(N / 16);
  for(int i = 0; i < N; i += 16) {
    int elem = 0;
    for(int j = 0; j < 16 && i + j < N; j++) {
      elem ^= list[i + j];
    }
    hash[i / 16] = elem;
  }
  return hash;
}

int main() {
  string input; cin >> input;
  for(int byte : knotHash(input)) {
    cout << setw(2) << setfill('0') << hex << byte;
  }
  cout << endl;
  return 0;
}
