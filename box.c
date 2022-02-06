#include "gba.h"
#include "box.h"

#define COLOR_WHITE BGR(31, 31, 31)
#define COLOR_BLACK 0

void draw_box(struct box *b, int x, int y, hword color){
  hword *base, *d;
  int w,h;

  /* Base point is at (x, y). */
  base = (hword*)VRAM + LCD_WIDTH * y + x;

  /* Draw box from (x, y). */
  for (h = b->height; h > 0; h--) {
    d = base;
    for (w = b->width; w > 0; w--) *(d++) = color;
    base += LCD_WIDTH;
  }

  /* Set the current position. */
  b->x = x;
  b->y = y;
}

void move_box(struct box *b, int x, int y, hword color){
  draw_box(b, b->x, b->y, COLOR_BLACK);
  draw_box(b, x, y, color);
}

int cross(struct box *b1, struct box *b2){
  // b1とb2の領域が重なっていれば1，重なっていなければ0を返す
  if(b1->y <= b2->y + b2->height &&
     b1->y + b1->height >= b2->y &&
     b1->x <= b2->x + b2->width &&
     b1->x + b1->width >= b2->x){
    if(b2->x <= b1->x && b1->x <= b2->x + b2->width){
      return 0;
    }else if(b1->x <= b2->x && b2->x + b2->width <= b1->x + b1->width){
      return 1;
    }else if(b2->x <= b1->x + b1->width && b1->x + b1->width <= b2->x + b2->width){
      return 2;
    }
  }else{
    return 3;
  }
}

/*int cross(struct box *b1, struct box *b2){
  // b1とb2の領域が重なっていれば1，重なっていなければ0を返す
  if(b1->x <= b2->x + b2->width && b1->x + b1->width >= b2->x){
    if(b1->y + b1->height >= b2->y && b1->y <= b2->y + b2->height){
      return 1;
    }else{
      return 0;
    }
  }else{
    return 0;
  }
}*/
