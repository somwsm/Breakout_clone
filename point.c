#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0
#define FONT_SIZE 8

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

void wait(int val){
  int i,j;

  for(i = 0; i < val; i++){
    for(j = 0; j < val; j++){}
  }
}

int main(){
  hword *fb = (hword*)VRAM;
  int key,i;

  /* Initialize LCD Control Register to use Mode 3. */
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

  /*
   * Loop forever reading a key status and displaying the
   * corresponding character.
   */
   if (! (key & KEY_START)){
     for (;;) {
        /* Read a key status from Key Status Register. */
        key = gba_register(KEY_STATUS);

        wait(200);

        if (! (key & KEY_DOWN)){
          i += 240*8;
          draw_char(fb + i, COLOR_WHITE, 2) ;
        }

        if (! (key & KEY_UP)){
          i -= 240*8;
          draw_char(fb + i, COLOR_WHITE, 2) ;
        }

        if (! (key & KEY_LEFT)){
          i -= 8;
          draw_char(fb + i, COLOR_WHITE, 2) ;
        }

        if (! (key & KEY_RIGHT)){
          i += 8;
          draw_char(fb + i, COLOR_WHITE, 2);
        }
      }
   }
}
