#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>

#define ORE_STOCK 1000000000000LL

using namespace std;

typedef long long ll;

map<string, pair<int, map<string, int>>> graph;

void read() {
  int qty; char chemical[10];
  map<string, int> reqs;
  while(scanf("%d %[A-Z],", &qty, chemical) == 2) {
    reqs[chemical] = qty;
    if(scanf(" => %d %s", &qty, chemical) == 2) {
      graph[chemical] = {qty, reqs};
      reqs.clear();
    }
  }
}

ll oreNeeded(ll fuelUnits) {
  map<string, ll> stock;
  map<string, ll> needed;
  needed["FUEL"] = fuelUnits;

  ll oreCnt = 0;
  while(!needed.empty()) {
    auto neededEntry = *needed.begin();
    if(neededEntry.first == "ORE") {
      oreCnt += neededEntry.second;
      needed.erase(neededEntry.first);
      continue;
    }
    if(stock[neededEntry.first] < neededEntry.second) {
      auto& prodRule = graph[neededEntry.first];
      ll prodTimes = (neededEntry.second - stock[neededEntry.first]
        + prodRule.first - 1) / prodRule.first;

      stock[neededEntry.first] += prodTimes * prodRule.first;
      for(auto& e : prodRule.second) {
        needed[e.first] += prodTimes * e.second;
      }
    }
    stock[neededEntry.first] -= neededEntry.second;
    needed.erase(neededEntry.first);
  }
  return oreCnt;
}

int main() {
  read();
  printf("%lld\n", oreNeeded(1));

  ll low = 0, high = 100000000LL;
  while(low < high) {
    ll mid = (high + low + 1) / 2;
    ll ore = oreNeeded(mid);

    if(ore > ORE_STOCK) high = mid - 1;
    else low = mid;
  }
  printf("%lld\n", low);
  return 0;
}
