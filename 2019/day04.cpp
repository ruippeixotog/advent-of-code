#include <cstdio>

bool hasEqualAdj(int k) {
  if(k < 10) return false;
  return k % 100 % 11 == 0 || hasEqualAdj(k / 10);
}

bool hasEqualAdj2(int k, int last = -1, int cnt = 0) {
  if(k % 10 != last && cnt == 2) return true;
  if(k == 0) return false;
  return hasEqualAdj2(k / 10, k % 10, k % 10 == last ? cnt + 1 : 1);
}

bool hasNonDecreasingDigits(int k) {
  if(k < 10) return true;
  return k % 10 >= k / 10 % 10 && hasNonDecreasingDigits(k / 10);
}

int main() {
  int low, high;
  scanf("%d-%d\n", &low, &high);

  int cnt1 = 0, cnt2 = 0;
  for(int k = low; k <= high; k++) {
    if(hasEqualAdj(k) && hasNonDecreasingDigits(k)) {
      cnt1++;
      if(hasEqualAdj2(k)) {
        cnt2++;
      }
    }
  }
  printf("%d %d\n", cnt1, cnt2);
  return 0;
}
