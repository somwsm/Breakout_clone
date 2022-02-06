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

int main(){
  hword *fb = (hword*)VRAM;
  int key,oldkey;

  /* Initialize LCD Control Register to use Mode 3. */
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

  /*
   * Loop forever reading a key status and displaying the
   * corresponding character.
   */
   for (;;) {
      /* Read a key status from Key Status Register. */
      oldkey = key;
      key = gba_register(KEY_STATUS);

      if (! (key & KEY_L)) draw_char(fb + 10, COLOR_WHITE, 'L' );
      else if(! (oldkey & KEY_L)) draw_char(fb+10, COLOR_BLACK, 'L');

      if (! (key & KEY_R)) draw_char(fb + 20, COLOR_WHITE, 'R' );
      else if(! (oldkey & KEY_R)) draw_char(fb+20, COLOR_BLACK, 'R');

      if (! (key & KEY_DOWN)) draw_char(fb + 30, COLOR_WHITE, 25) ;
      else if(! (oldkey & KEY_DOWN)) draw_char(fb+30, COLOR_BLACK, 25);

      if (! (key & KEY_UP)) draw_char(fb + 40, COLOR_WHITE, 24) ;
      else if(! (oldkey & KEY_UP)) draw_char(fb+40, COLOR_BLACK, 24);

      if (! (key & KEY_LEFT)) draw_char(fb + 50, COLOR_WHITE, 27) ;
      else if(! (oldkey & KEY_LEFT)) draw_char(fb+50, COLOR_BLACK, 27);

      if (! (key & KEY_RIGHT)) draw_char(fb + 60, COLOR_WHITE, 26);
      else if(! (oldkey & KEY_RIGHT)) draw_char(fb+60, COLOR_BLACK, 26);

      if (! (key & KEY_START)) draw_char(fb + 70, COLOR_WHITE, 'S' );
      else if(! (oldkey & KEY_START)) draw_char(fb+70, COLOR_BLACK, 'S');

      if (! (key & KEY_SELECT)) draw_char(fb + 80, COLOR_WHITE, 's' );
      else if(! (oldkey & KEY_SELECT)) draw_char(fb+80, COLOR_BLACK, 's');

      if (! (key & KEY_B)) draw_char(fb + 90, COLOR_WHITE, 'B' );
      else if(! (oldkey & KEY_B)) draw_char(fb+90, COLOR_BLACK, 'B');

      if (! (key & KEY_A)) draw_char(fb + 100, COLOR_WHITE, 'A');
      else if(! (oldkey & KEY_A)) draw_char(fb+100, COLOR_BLACK, 'A');
    }
}
