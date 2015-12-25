#include <iostream>
#include <vector>

#define ll long long

#define INF 1e8
#define MAXN 50

using namespace std;

int groups = 3;

int n;
int presents[MAXN];

int groupSum;
bool group1[MAXN];
int bestCnt = INF; ll bestQe = INF * INF;

bool dfs2(int k, vector<int>& rems) {
  if(k == n) return true;
  if(group1[k]) return dfs2(k + 1, rems);

  for(int i = 0; i < groups - 1; i++) {
    if(rems[i] >= presents[k]) {
      rems[i] -= presents[k];
      bool res = dfs2(k + 1, rems);
      rems[i] += presents[k];
      if(res) return true;
    }
  }
  return false;
}

void dfs1(int k, int cnt, ll qe, int rem) {
  if(cnt > bestCnt || (cnt == bestCnt && qe >= bestQe)) return;

  if(k == n) {
    vector<int> rems(groups, groupSum);
    if(rem == 0 && dfs2(0, rems)) {
      bestCnt = cnt; bestQe = qe;
    }
    return;
  }

  dfs1(k + 1, cnt, qe, rem);
  if(rem >= presents[k]) {
    group1[k] = true;
    dfs1(k + 1, cnt + 1, qe * presents[k], rem - presents[k]);
    group1[k] = false;
  }
}

int main() {
  while(cin >> presents[n]) { n++; }

  int sum = 0;
  for(int i = 0; i < n; i++)
    sum += presents[i];

  groupSum = sum / groups;
  dfs1(0, 0, 1, groupSum);
  cout << bestQe << endl;
  return 0;
}
