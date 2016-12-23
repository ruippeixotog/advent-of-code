#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

string password = "fbgdceah";

// note: the original input should be reversed first with `tail -r`
int main() {
  string str;
  while(getline(cin, str)) {
    int pos1, pos2; char ch1, ch2, dir[6];

    if(sscanf(str.c_str(), "swap position %d with position %d", &pos1, &pos2) == 2) {
      char tmp = password[pos2];
      password[pos2] = password[pos1];
      password[pos1] = tmp;
    }
    else if(sscanf(str.c_str(), "swap letter %c with letter %c", &ch1, &ch2) == 2) {
      for(int i = 0; i < password.length(); i++) {
        if(password[i] == ch1) password[i] = ch2;
        else if(password[i] == ch2) password[i] = ch1;
      }
    }
    else if(sscanf(str.c_str(), "rotate %s %d steps", dir, &pos1) == 2) {
      if(string(dir) == "left") pos1 = password.length() - pos1;
      password = password.substr(pos1) + password.substr(0, pos1);
    }
    else if(sscanf(str.c_str(), "rotate based on position of letter %c", &ch1) == 1) {
      int after = password.find(ch1);

      for(int i = 0; i < password.length(); i++) {
        int rot = i >= 4 ? i + 2 : i + 1;

        if((i + rot) % password.length() == after) {
          rot = (after - i + password.length()) % password.length();
          password = password.substr(rot) + password.substr(0, rot);
          break;
        }
      }
    }
    else if(sscanf(str.c_str(), "reverse positions %d through %d", &pos1, &pos2) == 2) {
      reverse(password.begin() + pos1, password.begin() + pos2 + 1);
    }
    else if(sscanf(str.c_str(), "move position %d to position %d", &pos1, &pos2) == 2) {
      char tmp = password[pos2];
      password.erase(pos2, 1);
      password.insert(pos1, 1, tmp);
    }
    else {
      fprintf(stderr, "ERROR: unrecognized instruction '%s'\n", str.c_str());
    }
  }

  printf("%s\n", password.c_str());
  return 0;
}
