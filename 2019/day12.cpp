#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

vector<int> posX, posY, posZ, velX, velY, velZ;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
int sig(int k) { return k == 0 ? 0 : k / abs(k); }

void doStep(vector<int>& pos, vector<int>& vel) {
  for(int i = 0; i < pos.size(); i++) {
    for(int j = 0; j < pos.size(); j++) {
      vel[i] = vel[i] + sig(pos[j] - pos[i]);
    }
  }
  for(int i = 0; i < pos.size(); i++) {
    pos[i] = pos[i] + vel[i];
  }
}

int energyAfter(int n) {
  vector<int> posX2 = posX, posY2 = posY, posZ2 = posZ,
              velX2 = velX, velY2 = velY, velZ2 = velZ;

  for(int step = 0; step < n; step++) {
    doStep(posX2, velX2);
    doStep(posY2, velY2);
    doStep(posZ2, velZ2);
  }
  int totalEnergy = 0;
  for(int i = 0; i < posX2.size(); i++) {
    totalEnergy += (abs(posX2[i]) + abs(posY2[i]) + abs(posZ2[i])) *
                   (abs(velX2[i]) + abs(velY2[i]) + abs(velZ2[i]));
  }
  return totalEnergy;
}

int findPeriod(vector<int>& pos, vector<int>& vel) {
  vector<int> initialPos = pos, initialVel = vel;

  int step = 0;
  do {
    doStep(pos, vel);
    step++;
  } while(pos != initialPos || vel != initialVel);
  return step;
}

int main() {
  int x, y, z;
  while(scanf("<x=%d, y=%d, z=%d>\n", &x, &y, &z) == 3) {
    posX.push_back(x); posY.push_back(y); posZ.push_back(z);
  }
  velX.resize(posX.size());
  velY.resize(posY.size());
  velZ.resize(posZ.size());

  printf("%d\n", energyAfter(1000));

  int px = findPeriod(posX, velX);
  int py = findPeriod(posY, velY);
  int pz = findPeriod(posZ, velZ);
  printf("%lld\n", lcm(lcm(px, py), pz));
  return 0;
}
