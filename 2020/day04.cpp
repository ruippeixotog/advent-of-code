#include <cstdio>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

string reqKeys[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
smatch m;

inline int between(int n, int low, int high) {
  return n >= low && n <= high;
}

bool validateRange(string& entry, string key, int low, int high) {
  return regex_search(entry, m, regex(".* " + key + ":([0-9]+) .*")) &&
    between(stoi(m[1]), low, high);
}

bool validateHeight(string& entry) {
  return regex_search(entry, m, regex(".* hgt:([0-9]+)(cm|in) .*")) &&
    ((m[2] == "cm" && between(stoi(m[1]), 150, 193)) ||
      (m[2] == "in" && between(stoi(m[1]), 59, 76)));
}

bool validate1(string& entry) {
  for(auto reqKey : reqKeys) {
    if(!regex_match(entry, regex(".* " + reqKey + ":.*"))) {
      return false;
    }
  }
  return true;
}

bool validate2(string& entry) {
  return validateRange(entry, "byr", 1920, 2002) &&
    validateRange(entry, "iyr", 2010, 2020) &&
    validateRange(entry, "eyr", 2020, 2030) &&
    validateHeight(entry) &&
    regex_match(entry, regex(".* hcl:#[0-9a-f]{6} .*")) &&
    regex_match(entry, regex(".* ecl:(amb|blu|brn|gry|grn|hzl|oth) .*")) &&
    regex_match(entry, regex(".* pid:[0-9]{9} .*"));
}

int main() {
  int cnt1 = 0, cnt2 = 0;
  string entry, line;
  while(getline(cin, line)) {
    if(!line.empty()) {
      entry += " " + line + " ";
      continue;
    }
    cnt1 += validate1(entry);
    cnt2 += validate2(entry);
    entry.clear();
  }
  cnt1 += validate1(entry);
  cnt2 += validate2(entry);
  printf("%d %d\n", cnt1, cnt2);
  return 0;
}
