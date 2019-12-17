#include <cstdio>
#include <vector>

#define PHASES 100
#define REPS 10000
#define SOL_LEN 8

int baseAmp[] = {0, 1, 0, -1};

using namespace std;

void print(const vector<int>& ls, int idx) {
  for(int i = idx; i < idx + SOL_LEN; i++) {
    printf("%d", ls[i]);
  }
  printf("\n");
}

void fft1(vector<int> ls, int phases) {
  while(phases--) {
    vector<int> newLs;
    for(int i = 0; i < ls.size(); i++) {
      int newElem = 0;
      for(int j = 0; j < ls.size(); j++) {
        int weight = baseAmp[(j + 1) % (4 * (i + 1)) / (i + 1)];
        newElem += weight * ls[j];
      }
      newLs.push_back(abs(newElem) % 10);
    }
    ls = newLs;
  }
  print(ls, 0);
}

void fft2(const vector<int>& ls, int phases, int idx) {
  int totalLen = (int) ls.size() * REPS;
  vector<int> mults(totalLen - idx, 0);
  mults[0] = 1;
  while(phases--) {
    for(int i = 1; i < totalLen - idx; i++) {
      mults[i] = (mults[i] + mults[i - 1]) % 10;
    }
  }

  vector<int> newLs;
  for(int i = 0; i < SOL_LEN; i++) {
    int newElem = 0;
    for(int j = 0; j < mults.size() - i; j++) {
      newElem = (newElem + mults[j] * ls[(idx + i + j) % ls.size()]) % 10;
    }
    newLs.push_back(newElem % 10);
  }
  print(newLs, 0);
}

int main() {
  vector<int> ls;
  char ch;
  while(scanf("%c", &ch) > 0 && ch >= '0' && ch <= '9') {
    ls.push_back(ch - '0');
  }

  int idx = 0;
  for(int i = 0; i < 7; i++) {
    idx = (idx * 10) + ls[i];
  }
  fft1(ls, PHASES);
  fft2(ls, PHASES, idx);
  return 0;
}
