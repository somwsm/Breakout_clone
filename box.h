#ifndef BOX_H //二重でincludeされることを防ぐ
#define BOX_H

struct box {
  int x, y;
  int width, height;
};

void draw_box(struct box *b, int x, int y, hword color);
void move_box(struct box *b, int x, int y, hword color);
int cross(struct box *b1, struct box *b2);

#endif
