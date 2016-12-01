#include <cstdio>
#include <iostream>

#define INF 1e8

using namespace std;

int dfs(int pHp, int pMp, int eHp, int eDmg,
        int shld, int psn, int rch, bool pTurn, int cost) {
  if(psn) { eHp -= 3; psn--; }
  if(rch) { pMp += 101; rch--; }
  if(shld) { shld--; }
  if(pTurn) pHp--;

  if(pHp <= 0) return INF;
  if(eHp <= 0) return cost;

  if(!pTurn) {
    return dfs(pHp - max(1, eDmg - (shld ? 7 : 0)), pMp, eHp, eDmg,
      shld, psn, rch, !pTurn, cost);
  }

  int best = INF;
  if(pMp >= 53) {
    best = min(best, dfs(pHp, pMp - 53, eHp - 4, eDmg,
      shld, psn, rch, !pTurn, cost + 53));
  }
  if(pMp >= 73) {
    best = min(best, dfs(pHp + 2, pMp - 73, eHp - 2, eDmg,
      shld, psn, rch, !pTurn, cost + 73));
  }
  if(pMp >= 113 && !shld) {
    best = min(best, dfs(pHp, pMp - 113, eHp, eDmg,
      6, psn, rch, !pTurn, cost + 113));
  }
  if(pMp >= 173 && !psn) {
    best = min(best, dfs(pHp, pMp - 173, eHp, eDmg,
      shld, 6, rch, !pTurn, cost + 173));
  }
  if(pMp >= 229 && !rch) {
    best = min(best, dfs(pHp, pMp - 229, eHp, eDmg,
      shld, psn, 5, !pTurn, cost + 229));
  }
  return best;
}

int main() {
  int eHp, eDmg;
  scanf("Hit Points: %d\nDamage: %d", &eHp, &eDmg);
  cout << dfs(50, 500, eHp, eDmg, 0, 0, 0, true, 0) << endl;
  return 0;
}
