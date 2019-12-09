#include <cstdio>
#include <cstring>

#define LAYERS 100
#define W 25
#define H 6

int img[LAYERS][H][W];

int checksum() {
  int minZeros = W * H + 1, res = 0;
  for(int layer = 0; layer < LAYERS; layer++) {
    int hist[10];
    memset(hist, 0, sizeof(hist));

    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        hist[img[layer][i][j]]++;
      }
    }
    if(hist[0] < minZeros) {
      minZeros = hist[0];
      res = hist[1] * hist[2];
    }
  }
  return res;
}

void render() {
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      for(int layer = 0; layer < LAYERS; layer++) {
        int v = img[layer][i][j];
        if(v == 2) continue;
        printf("%c ", v == 0 ? ' ' : '*');
        break;
      }
    }
    printf("\n");
  }
}

int main() {
  for(int layer = 0; layer < LAYERS; layer++) {
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        char ch; scanf("%c", &ch);
        img[layer][i][j] = ch - '0';
      }
    }
  }

  printf("%d\n", checksum());
  render();
  return 0;
}
