#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     BGR(0, 0, 0)

hwoed *tile = (hword*) VRAM_TILE(0);
hword *map = (hword*) VRAM_MAP(28);

int x = 0, y = 0;

void init_screen() {
  int i, row, col, bit, val;

  for(i = 0; i < LCD_PAL_COLORS; i++){
    for(row = 0; row < 8; row++){
      for(col = 7; col >= 0; col--){
        bit = (char8x8[i][row]) & (1 << col) ? 2:1;
        if(col % 2) val = bit;
        else tile[(i*LCD_VWIDTH) + (row*4) + ((7-col) / 2)] = \ val + (bit << 8);
      }
    }
  }

  gba_resister(LCD_BG0) = LCD_SIZE3232 |
                          LCD_COLOR256 |
                          LCD_BGTILE(0) |
                          LCD_BGMAP(28);
  gba_resister(LCD_CTRL) = LCD_MODE0 |
                           LCD_BG0EN;
}

void locate(int xx, int yy){
  x = xx;
  y = yy;
}

void print(const char* str){
  const char* ptr = str;

  while(*ptr){
    map[y*LCD_VHEIGHT+ x++] = *ptr++;
  }
}

int main(){
  init_screen();

  locate(5,9);
  prints("\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
  locate(5,10);

  prints("\xba \x01 Hello, world! \x02 xba");
  locate(5,11);
  prints("\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");

  for(;;){}
}
