#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

typedef long long ll;

using namespace std;

map<string, tuple<int, int, int, int>> fields;
vector<int> myTicket;
vector<vector<int>> othTickets;

bool isValid(string field, int val) {
  int low1, hi1, low2, hi2; 
  tie(low1, hi1, low2, hi2) = fields[field];
  if((val >= low1 && val <= hi1) || (val >= low2 && val <= hi2)) {
    return true;
  }
  return false;
}

bool isAnyValid(int val) {
  for(auto& e : fields) {
    if(isValid(e.first, val)) return true;
  }
  return false;
}

bool allCompleted(vector<set<string>>& possibleFields) {
  for(auto& col : possibleFields) {
    if(col.size() > 1) return false;
  }
  return true;
}

void readIntList(const string& line, vector<int>& vec) {
  int last = 0, next = 0;
  while ((next = line.find(",", last)) != -1) {
    vec.push_back(stoi(line.substr(last, next - last)));
    last = next + 1;
  }
  vec.push_back(stoi(line.substr(last)));
}

int main() {
  char name[50]; int low1, hi1, low2, hi2;
  string line;
  while(getline(cin, line) && !line.empty()) {
    sscanf(line.c_str(), "%[a-z ]: %d-%d or %d-%d\n", name, &low1, &hi1, &low2, &hi2);
    fields[name] = {low1, hi1, low2, hi2};
  }
  getline(cin, line);
  getline(cin, line);
  readIntList(line, myTicket);

  getline(cin, line);
  getline(cin, line);
  while(getline(cin, line) && !line.empty()) {
    vector<int> newTicket;
    readIntList(line, newTicket);
    othTickets.push_back(newTicket);
  }

  vector<vector<int>> validTickets = {myTicket};
  int res1 = 0;
  for(auto ticket : othTickets) {
    bool valid = true;
    for(auto val : ticket) {
      if(!isAnyValid(val)) { res1 += val; valid = false; }
    }
    if(valid) validTickets.push_back(ticket);
  }

  vector<set<string>> possibleFields(myTicket.size());
  for(int col = 0; col < myTicket.size(); col++) {
    for(auto& e : fields) {
      bool colValid = true;
      for(int i = 0; i < validTickets.size(); i++) {
        if(!isValid(e.first, validTickets[i][col])) colValid = false;
      }
      if(colValid) possibleFields[col].insert(e.first);
    }
  }
  while(!allCompleted(possibleFields)) {
    for(int col = 0; col < myTicket.size(); col++) {
      if(possibleFields[col].size() == 1) {
        for(int col2 = 0; col2 < myTicket.size(); col2++) {
          if(col != col2) {
            possibleFields[col2].erase(*possibleFields[col].begin());
          }
        }
      }
    }
  }
  ll res2 = 1;
  for(int i = 0; i < myTicket.size(); i++) {
    if(possibleFields[i].begin()->rfind("departure") == 0) {
      res2 *= myTicket[i];
    }
  }
  printf("%d %lld\n", res1, res2);
  return 0;
}
