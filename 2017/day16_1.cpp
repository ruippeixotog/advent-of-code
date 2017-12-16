#include <cstdio>
#include <string>

using namespace std;

string progs = "abcdefghijklmnop";

int main() {
  while(true) {
    int arg1, arg2; char p1, p2;
    if(scanf("s%d,", &arg1) == 1) {
      progs = progs.substr(progs.length() - arg1) +
              progs.substr(0, progs.length() - arg1);

    } else if(scanf("x%d/%d,", &arg1, &arg2) == 2) {
      swap(progs[arg1], progs[arg2]);

    } else if(scanf("p%c/%c,", &p1, &p2) == 2) {
      arg1 = progs.find(p1), arg2 = progs.find(p2);
      swap(progs[arg1], progs[arg2]);

    } else {
      break;
    }
  }
  printf("%s\n", progs.c_str());
  return 0;
}
