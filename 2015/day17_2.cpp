#include <iostream>

#define MAXN 50
#define INF 1e9

using namespace std;

int n;
int cs[MAXN];

int dfs(int k, int rem, int cnt) {
  if(k == n) { return rem == 0 ? cnt : INF; }
  return min(dfs(k + 1, rem, cnt), dfs(k + 1, rem - cs[k], cnt + 1));
}

int main() {
  while(cin >> cs[n]) { n++; }
  cout << dfs(0, 150, 0) << endl;
  return 0;
}
