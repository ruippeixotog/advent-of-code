#include <cstdio>
#include <iostream>
#include <vector>

#define INF 1e8

using namespace std;

struct Item {
  int cost, dmg, arm;
  Item(int c, int d, int a): cost(c), dmg(d), arm(a) {}
  Item operator+(const Item& i) {
    return Item(cost + i.cost, dmg + i.dmg, arm + i.arm);
  }
};

Item noItem(0, 0, 0);

vector<Item> weapons = { Item(8, 4, 0), Item(10, 5, 0), Item(25, 6, 0),
  Item(40, 7, 0), Item(74, 8, 0) };

vector<Item> armor = { Item(13, 0, 1), Item(31, 0, 2), Item(53, 0, 3),
  Item(75, 0, 4), Item(102, 0, 5), noItem };

vector<Item> rings = { Item(25, 1, 0), Item(50, 2, 0), Item(100, 3, 0),
  Item(20, 0, 1), Item(40, 0, 2), Item(80, 0, 3), noItem, noItem };

bool sim(int pHp, int pDmg, int pArm, int eHp, int eDmg, int eArm) {
  bool pTurn = true;
  while(pHp > 0 && eHp > 0) {
    if(pTurn) { eHp -= max(1, pDmg - eArm); }
    else { pHp -= max(1, eDmg - pArm); }
    pTurn = !pTurn;
  }
  return pHp > 0;
}

int main() {
  int eHp, eDmg, eArm;
  scanf("Hit Points: %d\nDamage: %d\nArmor: %d", &eHp, &eDmg, &eArm);

  int best = 0;
  for(int w = 0; w < weapons.size(); w++) {
    for(int a = 0; a < armor.size(); a++) {
      for(int r1 = 0; r1 < rings.size(); r1++) {
        for(int r2 = 0; r2 < rings.size(); r2++) {
          if(r1 == r2) continue;
          Item comb = weapons[w] + armor[a] + rings[r1] + rings[r2];
          if(!sim(100, comb.dmg, comb.arm, eHp, eDmg, eArm)) {
            best = max(best, comb.cost);
          }
        }
      }
    }
  }

  cout << best << endl;
  return 0;
}
