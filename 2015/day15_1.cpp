#include <iostream>

#define MAXN 10

using namespace std;

bool readEntry(int& v1, int& v2, int& v3, int& v4) {
  int res = scanf("%*s capacity %d, durability %d, ", &v1, &v2);
  scanf("flavor %d, texture %d, calories %*d", &v3, &v4);
  return res > 0;
}

int n;
int v1s[MAXN], v2s[MAXN], v3s[MAXN], v4s[MAXN];

int dfs(int k, int rem, int s1, int s2, int s3, int s4) {
  if(k == n) {
    return max(s1, 0) * max(s2, 0) * max(s3, 0) * max(s4, 0);
  }
  int best = 0;
  for(int i = 0; i <= rem; i++) {
    best = max(best, dfs(k + 1, rem - i, s1 + v1s[k] * i, s2 + v2s[k] * i,
      s3 + v3s[k] * i, s4 + v4s[k] * i));
  }
  return best;
}

int main() {
  while(readEntry(v1s[n], v2s[n], v3s[n], v4s[n])) { n++; }
  cout << dfs(0, 100, 0, 0, 0, 0) << endl;
  return 0;
}
