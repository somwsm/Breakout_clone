#include "gba.h"
#include "box.h"
#include "ball.h"
#include "block.h"
#include "game.h"
#include "8x8.til"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0
#define FONT_SIZE 8

static enum state current_state;  // 現在の状態
int count = 0;
hword *fb = (hword*)VRAM;

/*
* Draw a font of code with color.
* ptr specifies the font's top left corner.
*/
void draw_char(hword *ptr, hword color, int code){
  hword   *p;
  int     i, j;
  unsigned char   *font = char8x8[code];

  for (i = 0; i < FONT_SIZE; i++) {
    p = ptr + LCD_WIDTH * i;
    for (j = FONT_SIZE - 1; j >= 0; j--, p++) {
      if (font[i] & (1 << j)) *p = color;
    }
  }
}

void game_over(hword color){
  draw_char(fb + (LCD_WIDTH * 10) + 12316, color, 71);
  draw_char(fb + (LCD_WIDTH * 10) + 12324, color, 65);
  draw_char(fb + (LCD_WIDTH * 10) + 12332, color, 77);
  draw_char(fb + (LCD_WIDTH * 10) + 12340, color, 69);
  draw_char(fb + (LCD_WIDTH * 10) + 12348, color, 32);
  draw_char(fb + (LCD_WIDTH * 10) + 12356, color, 79);
  draw_char(fb + (LCD_WIDTH * 10) + 12364, color, 86);
  draw_char(fb + (LCD_WIDTH * 10) + 12372, color, 69);
  draw_char(fb + (LCD_WIDTH * 10) + 12380, color, 82);
  draw_char(fb + (LCD_WIDTH * 10) + 12388, color, 33);
}

void game_clear(hword color){
  draw_char(fb + (LCD_WIDTH * 10) + 12340, color, 67);
  draw_char(fb + (LCD_WIDTH * 10) + 12348, color, 76);
  draw_char(fb + (LCD_WIDTH * 10) + 12356, color, 69);
  draw_char(fb + (LCD_WIDTH * 10) + 12364, color, 65);
  draw_char(fb + (LCD_WIDTH * 10) + 12372, color, 82);
  draw_char(fb + (LCD_WIDTH * 10) + 12380, color, 33);
}

int game_get_count() { return count; }

enum state game_get_state(void) { return current_state; }
void game_set_state(enum state new_state) {
  current_state = new_state;
}

void game_step(void)
{
  int key = gba_register(KEY_STATUS);

  switch (game_get_state()) {
  case START:
    game_clear(COLOR_BLACK);
    game_over(COLOR_BLACK);
    if (! (key & KEY_START)){
      game_set_state(RUNNING);
    }
    break;

  case RUNNING:
    if (ball_get_box()->y + ball_get_box()->height > 160){
      game_set_state(DEAD);
    }
    if(block_get_num() == 0){
      game_set_state(CLEAR);
    }
    break;

  case DEAD:
    if(count == 2){
      game_over(COLOR_WHITE);
    }
    if(! (key & KEY_START) && count < 3){
      count++;
      if(count == 3){
        count = 0;
        game_set_state(START);
      }else{
        game_set_state(RESTART);
      }
    }
    break;

  case RESTART:
    /* 次のティックはRUNNING状態にする．*/
    if(! (key & KEY_START)){
      game_set_state(RUNNING);
    }
    break;

  case CLEAR:
    game_clear(COLOR_WHITE);
    if(! (key & KEY_START)){
      count = 0;
      game_set_state(START);
    }
    break;
  }
}
