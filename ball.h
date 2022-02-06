#ifndef BALL_H //二重でincludeされることを防ぐ
#define BALL_H

int ball_get_dy(void);             // ボールのy方向の速度を返す．
int ball_get_dx(void);             // ボールのy方向の速度を返す．
void ball_set_dy(int new_dy);      // ボールのy方向の速度をセットする．
void ball_set_dx(int new_dx);      // ボールのx方向の速度をセットする．
struct box *ball_get_box(void);    // ボールの箱の位置を返す．
void ball_step(void);              // アニメーションの1ステップを行なう．p(void);

#endif
