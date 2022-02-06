#include "gba.h"
#include "box.h"
#include "game.h"
#include "ball.h"
#include "racket.h"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0

static int dx = 2;
static int dy = 3;         /* ボールの現在の速度 */
static struct box ball = {25,129,9,9};        /* ボールの箱の現在の位置 */
static struct box firstball = {25,129,9,9};

void first_ball(){
  dx = 2;
  dy = 3;         /* ボールの現在の速度 */
  ball = firstball;
  draw_box(&ball,ball.x,ball.y,COLOR_WHITE);
}

int ball_get_dy() { return dy; }
int ball_get_dx() { return dx; }
void ball_set_dy(int new_dy) { dy = new_dy; }
void ball_set_dx(int new_dx) { dx = new_dx; }
struct box *ball_get_box() { return &ball; }

void ball_step(void)
{
  switch (game_get_state()) {
  case START:
    draw_box(&ball, ball.x, ball.y, COLOR_BLACK);
    //ボールの位置，速度を初期状態にし，ボールを表示する．
    first_ball();
    break;
  case RUNNING:
    //ボールのアニメーションを1ステップ行なう．
    move_box(&ball,ball.x + dx,ball.y + dy,COLOR_WHITE);
    if(ball.x < 0 || ball.x + ball.width > 240){
      dx = -dx;
    }

    if(ball.y < 0){
      dy = -dy;
    }
    break;
  case DEAD:
    if(game_get_count() == 2){
      draw_box(&ball, ball.x, ball.y, COLOR_BLACK);
    }
    break;
  case RESTART:
    //現在のボールを画面から消し，
    draw_box(&ball, ball.x, ball.y, COLOR_BLACK);
    //ボールの位置，速度を初期状態にし，ボールを表示する．
    first_ball();
    break;
  case CLEAR:
    draw_box(&ball, ball.x, ball.y, COLOR_BLACK);
    break;
  }
}
