#include "gba.h"

void makesquare(int i, int j){
  hword *fb = (hword*)VRAM;
  int x, y;
  for(y = i; y < j; y += 9){
    for (x = i; x < j; x++) {
      *(fb + (LCD_WIDTH * y) + x) = BGR(0x1F, 0x1F, 0x1F);
    }
  }

  for(x = i; x < j; x += 9){
    for (y = i; y < j; y++) {
      *(fb + (LCD_WIDTH * y) + x) = BGR(0x1F, 0x1F, 0x1F);
    }
  }
}

main(){
  /* Initialize LCD Control Register to use Mode 3. */
  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;

  makesquare(20,30);

  /* spin forever here */
  for (;;) {}
}
