#include <algorithm>
#include <cstdio>
#include <list>
#include <vector>

using namespace std;

typedef long long ll;

list<int> marbles = {0};

list<int>::iterator cnext(list<int>::iterator it) {
  return next(it) == marbles.end() ? marbles.begin() : next(it);
}

list<int>::iterator cprev(list<int>::iterator it) {
  return prev(it == marbles.begin() ? marbles.end() : it);
}

int main() {
  int np, nm;
  scanf("%d players; last marble is worth %d points\n", &np, &nm);

  vector<ll> score(np, 0);
  int currPlayer = 0;
  auto curr = marbles.begin();
  for(int i = 1; i <= nm * 100; i++, currPlayer = (currPlayer + 1) % np) {
    if(i % 23 > 0) {
      curr = marbles.insert(cnext(cnext(curr)), i);
    } else {
      for(int j = 0; j < 6; j++) curr = cprev(curr);
      score[currPlayer] += i;
      score[currPlayer] += *cprev(curr);
      marbles.erase(cprev(curr));
    }
    if(i == nm) {
      printf("%lld\n", *max_element(score.begin(), score.end()));
    }
  }
  printf("%lld\n", *max_element(score.begin(), score.end()));
  return 0;
}
