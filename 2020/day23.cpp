#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

struct Node {
  int val; Node *next;
 
  Node(): next(this) {}
  void insertNext(Node* node) { node->next = next; next = node; }
};

vector<int> play(int moves, int n, vector<int> initials) {
  vector<Node> index(n + 1);

  int prevElem = initials[0];
  for(int i = 0; i < n; i++) {
    int elem = i < initials.size() ? initials[i] : i + 1;
    index[elem].val = elem;
    index[prevElem].insertNext(&index[elem]);
    prevElem = elem;
  }

  Node* curr = &index[initials[0]];
  for(int i = 0; i < moves; i++, curr = curr->next) {
    int head = curr->val;
    int seq[3];
    for(int i = 0; i < 3; i++, curr->next = curr->next->next) {
      seq[i] = curr->next->val;
    }
    int target = head - 1;
    while(target < 1 || find(seq, seq + 3, target) != seq + 3) {
      target = target < 1 ? n : target - 1;
    }
    index[seq[2]].next = index[target].next;
    index[target].next = &index[seq[0]];
  }
  vector<int> res;
  for(auto* node = index[1].next; res.size() < 8; node = node->next) {
    res.push_back(node->val);
  }
  return res;
}

int main() {
  auto res1 = play(100, 9, {1, 3, 7, 8, 2, 6, 4, 9, 5});
  auto res2 = play(10000000, 1000000, {1, 3, 7, 8, 2, 6, 4, 9, 5});
  for(int n : res1) printf("%d", n);
  printf(" %lld\n", res2[0] * (ll) res2[1]);
  return 0;
}
