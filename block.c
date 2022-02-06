#include "gba.h"
#include "ball.h"
#include "game.h"
#include "box.h"
#include "block.h"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0
#define BLOCK_TOP 0
#define BLOCK_WIDTH 48
#define BLOCK_HEIGHT 10

static int yoko = 5;
static int tate = 3;

static struct box boxes[5][3];
static char flags[5][3];
static int num_blocks = 15;
static struct box null = {0,0,0,0};
int updown,rightleft,delete1,delete2,delete3,delete4;

struct box *nowball;

int block_get_num() { return num_blocks; }

void first_blocks(){
  int l,r;
  for(l = 0; l < yoko; l++){
    for(r = 0; r < tate; r++){
      struct box box = {l * BLOCK_WIDTH, BLOCK_TOP + r * BLOCK_HEIGHT, BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1};
      boxes[l][r] = box;
      flags[l][r] = 1;
      draw_box(&boxes[l][r],boxes[l][r].x,boxes[l][r].y,COLOR_WHITE);
    }
  }
  num_blocks = 15;
}

void delete_blocks(){
  int l,r;
  for(l = 0; l < yoko; l++){
    for(r = 0; r < tate; r++){
      struct box box = {l * BLOCK_WIDTH, BLOCK_TOP + r * BLOCK_HEIGHT, BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1};
      boxes[l][r] = box;
      draw_box(&boxes[l][r],boxes[l][r].x,boxes[l][r].y,COLOR_BLACK);
    }
  }
}

static int hit(int x, int y){
  int i = x / BLOCK_WIDTH;
  int j = (y - BLOCK_TOP) / BLOCK_HEIGHT;

  if(0 <= i && i < yoko){
    if(0 <= j && j < tate){
      if(flags[i][j] == 1){
        return 1;
      }else{
        return 0;
      }
    }else{
      return 0;
    }
  }else{
    return 0;
  }
}

void block_step(void)
{
  switch (game_get_state()) {
  case START:
    first_blocks();
    break;
  case RUNNING:
    updown = 0;
    rightleft = 0;
    delete1 = 0;
    delete2 = 0;
    delete3 = 0;
    delete4 = 0;

    nowball = ball_get_box();
    if(hit(nowball->x,nowball->y) == 1){
      struct box hitbox = boxes[nowball->x / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT];
      draw_box(&hitbox,hitbox.x,hitbox.y,COLOR_BLACK);
      updown--;
      rightleft++;
      delete1++;
    }
    if(hit(nowball->x + nowball->width,nowball->y) == 1){
      struct box hitbox = boxes[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT];
      draw_box(&hitbox,hitbox.x,hitbox.y,COLOR_BLACK);
      updown--;
      rightleft--;
      delete2++;
    }
    if(hit(nowball->x + nowball->width,nowball->y + nowball->height) == 1){
      struct box hitbox = boxes[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT];
      draw_box(&hitbox,hitbox.x,hitbox.y,COLOR_BLACK);
      updown++;
      rightleft--;
      delete3++;
    }
    if(hit(nowball->x,nowball->y + nowball->height) == 1){
      struct box hitbox = boxes[nowball->x / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT];
      draw_box(&hitbox,hitbox.x,hitbox.y,COLOR_BLACK);
      updown++;
      rightleft++;
      delete4++;
    }

    if(delete1 == 1){
      boxes[nowball->x / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT] = null;
      if(flags[nowball->x / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT] == 1){
        flags[nowball->x / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT] = 0;
        num_blocks--;
      }
    }
    if(delete2 == 1){
      boxes[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT] = null;
      if(flags[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT] == 1){
        flags[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y - BLOCK_TOP) / BLOCK_HEIGHT] = 0;
        num_blocks--;
      }
    }
    if(delete3 == 1){
      boxes[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT] = null;
      if(flags[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT] == 1){
        flags[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT] = 0;
        num_blocks--;
      }
    }
    if(delete4 == 1){
      boxes[(nowball->x + nowball->width) / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT] = null;
      if(flags[nowball->x / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT] == 1){
        flags[nowball->x / BLOCK_WIDTH][(nowball->y + nowball->height - BLOCK_TOP) / BLOCK_HEIGHT] = 0;
        num_blocks--;
      }
    }

    int rey = ball_get_dy();
    int rex = ball_get_dx();
    if(updown != 0){
      ball_set_dy(-rey);
    }
    if(rightleft != 0){
      ball_set_dx(-rex);
    }
    break;
  case DEAD:
    if(game_get_count() == 2){
      delete_blocks();
    }
    break;
  case RESTART:
    first_blocks();
    break;
  case CLEAR:
    break;
  }
}
