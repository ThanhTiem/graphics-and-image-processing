
#ifndef CLIPPING_H
#define CLIPPING_H

#include "Vector2D.h"

struct rect
{
	int Left;
	int Right;
	int Bottom;
	int Top;
};
typedef struct rect RECT;
typedef int CODE;

#define LEFT 1      //(0001)
#define RIGHT 2     //(0010)
#define BOTTOM 4    //(0100)
#define TOP 8       //(1000)

RECT CreateWindow(int l, int r, int t, int b);
CODE Encode(RECT r, Vector2D P);
int CohenSutherland(RECT r, Vector2D P1, Vector2D P2, Vector2D &Q1, Vector2D &Q2);
void ClippingCohenSutherland(RECT r, Vector2D &P1, Vector2D &P2);
int SolveNonLinearEquation(int p, int q, float &t1, float &t2);
int LiangBarsky(RECT r, Vector2D P1, Vector2D P2, Vector2D &Q1, Vector2D &Q2);


#endif //GRAPHICS2D_CLIPPING_H
