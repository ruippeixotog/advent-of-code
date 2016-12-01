#include <iostream>

#define MAXN 50

using namespace std;

int n;
int cs[MAXN];

int dfs(int k, int rem) {
  if(k == n) { return rem == 0; }
  return dfs(k + 1, rem) + dfs(k + 1, rem - cs[k]);
}

int main() {
  while(cin >> cs[n]) { n++; }
  cout << dfs(0, 150) << endl;
  return 0;
}
