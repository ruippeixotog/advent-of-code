#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
  unordered_map<int, unordered_set<string>> subs;
  string id;
  while(getline(cin, id)) {
    for(unsigned int i = 0; i < id.length(); i++) {
      string sub = id.substr(0, i) + id.substr(i + 1);
      if(subs[i].count(sub)) {
        cout << sub << endl;
        return 0;
      }
      subs[i].insert(sub);
    }
  }
  return 0;
}
