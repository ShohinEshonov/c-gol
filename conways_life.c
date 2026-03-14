#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define HEIGHT 10
#define WIDTH 45

int grid[HEIGHT][WIDTH];
int next[HEIGHT][WIDTH];

typedef struct {
  int x;
  int y;
} Point;

enum {
  DEAD = 0,
  ALIVE = 1,
};

void initGrid(int grid[HEIGHT][WIDTH], Point pattern[], int pattern_size) {
  int pat_count = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      grid[i][j] = DEAD;
    }
  }

  for (int i = 0; i < pattern_size; i++) {
    int x = pattern[i].x;
    int y = pattern[i].y;

    if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH) {
      grid[y][x] = ALIVE;
    }
  }
}

void printGrid(int grid[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (grid[i][j] == ALIVE) {
        printf("#");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int checkNeighbors(int grid[HEIGHT][WIDTH], int x, int y) {
  int live = 0;
  int dead = 0;

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      if (dx == 0 && dy == 0) {
        continue;
      }

      int nx = (x + dx + HEIGHT) % HEIGHT;
      int ny = (y + dy + WIDTH) % WIDTH;
      if(grid[nx][ny] == ALIVE)
      {
        live++;
      }
    }
  }
  if(grid[x][y] == DEAD && live == 3)
  {
    return ALIVE;
  }
  if(grid[x][y] == ALIVE && (live == 2 || live == 3))
  {
    return ALIVE;
  }
  return DEAD;
}




void copyGrids(int grid[HEIGHT][WIDTH], int grid2[HEIGHT][WIDTH])
{
  for(int i = 0; i < HEIGHT; i++)
  {
    for(int j = 0; j < WIDTH; j++)
    {
      grid[i][j] = grid2[i][j];
    }
  }  
}



void simulateStep(int grid[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]){
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int state = checkNeighbors(grid, i, j);
      next[i][j] = state; 
    }
  }
  copyGrids(grid, next);
}

int main() {
  Point pattern[5] = {{0, 5}, {1, 6}, {2, 4}, {2, 5}, {2, 6}};
  initGrid(grid, pattern, 5);
  for(;;)
  {
    system("clear");
    printGrid(grid);
    simulateStep(grid, next);   
    usleep(100000); // 100ms
  }
  return 0;
}
