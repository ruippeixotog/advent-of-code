#include <cstdio>

int main() {
  int cnt1 = 0, cnt2 = 0;
  int low, hi; char ch, pass[32];
  while(scanf("%d-%d %c: %s\n", &low, &hi, &ch, pass) > 0) {
    int chCnt = 0;
    for(int i = 0; pass[i]; i++) {
      if(pass[i] == ch) chCnt++;
    }
    if(low <= chCnt && chCnt <= hi) cnt1++;
    if(pass[low - 1] == ch ^ pass[hi - 1] == ch) cnt2++;
  }
  printf("%d %d\n", cnt1, cnt2);
  return 0;
}
