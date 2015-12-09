#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#define MAXC 50
#define INF 10e8

using namespace std;

map<string, int> ids;
int graph[MAXC][MAXC];

istream& readEntry(string& city1, string& city2, int& dist) {
  string word;
  return cin >> city1 >> word >> city2 >> word >> dist;
}

int getOrAdd(string& city) {
  if(ids.count(city)) return ids[city];
  int id = ids[city] = ids.size();
  return id;
}

bool visited[MAXC];

int dfs(int k, int curr, int dist) {
  if(k == ids.size()) return dist;

  int best = 0;
  for(int i = 0; i < ids.size(); i++) {
    if(!visited[i] && graph[curr][i] > 0) {
      visited[i] = true;
      best = max(best, dfs(k + 1, i, dist + graph[curr][i]));
      visited[i] = false;
    }
  }
  return best;
}

int main() {
  string city1, city2; int dist;

  while(readEntry(city1, city2, dist)) {
    int c1 = getOrAdd(city1);
    int c2 = getOrAdd(city2);
    graph[c1][c2] = graph[c2][c1] = dist;
  }

  int best = 0;
  for(int i = 0; i < ids.size(); i++) {
    visited[i] = true;
    best = max(best, dfs(1, i, 0));
    visited[i] = false;
  }

  cout << best << endl;
  return 0;
}
