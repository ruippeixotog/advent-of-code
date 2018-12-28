#include <cstdio>
#include <vector>

using namespace std;

struct Node {
  vector<Node> children;
  vector<int> metadata;

  int metadataSum() {
    int sum = 0;
    for(Node& ch : children) sum += ch.metadataSum();
    for(int entry : metadata) sum += entry;
    return sum;
  };

  int value() {
    if(children.empty()) {
      return metadataSum();
    }
    int sum = 0;
    for(int entry : metadata) {
      if(entry > 0 && entry <= children.size()) {
        sum += children[entry - 1].value();
      }
    }
    return sum;
  }
};

Node readNode() {
  Node node;
  int nc, nm; scanf("%d %d", &nc, &nm);
  while(nc--) {
    node.children.push_back(readNode());
  }
  while(nm--) {
    int entry; scanf("%d", &entry);
    node.metadata.push_back(entry);
  }
  return node;
}

int main() {
  Node tree = readNode();
  printf("%d\n", tree.metadataSum());
  printf("%d\n", tree.value());
  return 0;
}
