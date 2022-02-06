#include "gba.h"
#include "box.h"
#include "game.h"
#include "ball.h"
#include "racket.h"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0

static struct box racket = {20,140,20,2};       /* ボールの箱の現在の位置 */
static struct box firstracket = {20,140,20,2};

void first_racket(){
  racket = firstracket;
  draw_box(&racket,racket.x,racket.y,COLOR_WHITE);
}

void racket_step(void)
{
  int key = gba_register(KEY_STATUS);

  switch (game_get_state()) {
  case START:
    draw_box(&racket, racket.x, racket.y, COLOR_BLACK);
    //ボールの位置，速度を初期状態にし，ボールを表示する．
    first_racket();
    break;
  case RUNNING:
    //ラケットのアニメーションを1ステップ行なう．
    draw_box(&racket, racket.x, racket.y, COLOR_WHITE);
    if (! (key & KEY_LEFT)){
      move_box(&racket,racket.x - 7,racket.y, COLOR_WHITE);
    }else if(! (key & KEY_RIGHT)){
      move_box(&racket,racket.x + 7,racket.y, COLOR_WHITE);
    }

    int rey = ball_get_dy();
    int rex = ball_get_dx();

    switch(cross(&racket,ball_get_box())){
      case 0:
        if(rex > 0){
          ball_set_dx(-rex);
        }
        ball_set_dy(-rey);
        break;
      case 1:
        ball_set_dy(-rey);
        break;
      case 2:
        if(rex < 0){
          ball_set_dx(-rex);
        }
        ball_set_dy(-rey);
        break;
      case 3:
        break;
    }
    break;
  case DEAD:
    if(game_get_count() == 2){
      draw_box(&racket, racket.x, racket.y, COLOR_BLACK);
    }
    break;
  case RESTART:
    //現在のラケットを画面から消し，
    draw_box(&racket, racket.x, racket.y, COLOR_BLACK);
    //ラケットの位置，速度を初期状態にし，ラケットを表示する．
    first_racket();
    break;
  case CLEAR:
    draw_box(&racket, racket.x, racket.y, COLOR_BLACK);
    break;
  }
}
