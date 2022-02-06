#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0
#define FONT_SIZE       8

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

void delay(hword val){
  hword *fb = (hword*)VRAM;
  int key;

  key = gba_register(KEY_STATUS);

  val += gba_register(TMR_COUNT0);
  while(val != gba_register(TMR_COUNT0)){
    if((key & KEY_START)){
      draw_char(fb + 60, COLOR_WHITE, 'S');
      val = gba_register(TMR_COUNT0);
    }
  }
}

int main(){
  hword *fb = (hword*)VRAM;
  int key;

  key = gba_register(KEY_STATUS);

  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
  gba_register(TMR_COUNT0) = 0;
  gba_register(TMR_CTRL0) = TMR_ENABLE + TMR_1024CLOCK;

  if(!(key & KEY_START)){
    draw_char(fb + 50, COLOR_WHITE, 'S');
    delay(0);
  }
}
