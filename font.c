#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0
#define FONT_SIZE       8

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

main(){
  hword   *fb = (hword*)VRAM;
  int i;

  /* Initialize LCD Control Register to use Mode 3. */
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

  /* Call draw_char to display 'A'. */
  for(i = 65; i < 70; i++){
    int p = 10*(i - 64);
    draw_char(fb + (LCD_WIDTH * 10) + p, COLOR_WHITE, i);
  }

  /* spin forever here */
  for (;;) {}
}
