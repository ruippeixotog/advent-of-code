#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

vector<int> row;

int findDiv(vector<int>& row) {
  for(int i = 0; i < row.size(); i++) {
    for(int j = 0; j < row.size(); j++) {
      if(i != j && row[i] % row[j] == 0)
        return row[i] / row[j];
    }
  }
  return -1;
}

int main() {
  string line; int sum = 0;
  while(getline(cin, line)) {
    istringstream sin(line);
    vector<int> row; int cell;
    while(sin >> cell) {
      row.push_back(cell);
    }
    sum += findDiv(row);
  }
  printf("%d\n", sum);
  return 0;
}
