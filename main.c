#include "gba.h"
#include "box.h"
#include "game.h"
#include "ball.h"
#include "racket.h"
#include "block.h"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0

// delay()関数などを定義...
/*void delay(){
  int i,j,val;
  int key = gba_register(KEY_STATUS);

  if(! (key & KEY_L)){
    val = 200;
  }else if(! (key & KEY_R)){
    val = 100;
  }else{
    val = 150;
  }

  for(i = 0; i < val; i++){
    for(j = 0; j < val; j++){}
  }
}

void wait_until(hword time){
  while (time != gba_register(TMR_COUNT0)){}
  ;
}*/

void wait_until_vblank(void) {
  while ((gba_register(LCD_STATUS) & 1) == 0)
  ;
}
void wait_while_vblank(void) {
  while ((gba_register(LCD_STATUS) & 1))
  ;
}

int main(void)
{
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

  int key;

  // 画面を初期化
  // タイマーを初期化
  while (1) {
    hword begin = gba_register(TMR_COUNT0);
    key = gba_register(KEY_STATUS);

    wait_until_vblank();  // 垂直ブランク期間になるまで待つ

    ball_step();
    racket_step();
    block_step();
    game_step();

    wait_while_vblank();  // 垂直ブランク期間が終るまで待つ
  }
}
