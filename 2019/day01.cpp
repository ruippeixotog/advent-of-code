#include <cstdio>

int calcFuel1(int mass) {
  return mass / 3 - 2;
}

int calcFuel2(int mass) {
  if(mass <= 0) return 0;
  int fuel = calcFuel1(mass);
  return (fuel < 0 ? 0 : fuel) + calcFuel2(fuel);
}

int main() {
  int totalFuel1 = 0, totalFuel2 = 0, mass;
  while(scanf("%d\n", &mass) > 0) {
    totalFuel1 += calcFuel1(mass);
    totalFuel2 += calcFuel2(mass);
  }
  printf("%d %d\n", totalFuel1, totalFuel2);
  return 0;
}
