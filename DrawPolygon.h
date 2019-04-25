#ifndef DRAWPOLYGON_H
#define DRAWPOLYGON_H
#include <SDL.h>
#include <cmath>
#include "Line.h"

void DrawEquilateralTriangle(int xc, int yc, int R, SDL_Renderer *ren);
void DrawSquare(int xc, int yc, int R, SDL_Renderer *ren);
void DrawPentagon(int xc, int yc, int R, SDL_Renderer *ren);
void DrawHexagon(int xc, int yc, int R, SDL_Renderer *ren);
void DrawStar(int xc, int yc, int R, SDL_Renderer *ren);
void DrawEmptyStar(int xc, int yc, int R, SDL_Renderer *ren);
void DrawStarEight(int xc, int yc, int R, SDL_Renderer *ren);
void DrawStarAngle(int xc, int yc, int R, float startAngle, SDL_Renderer *ren);
void DrawConvergentStar(int xc, int yc, int R, SDL_Renderer *ren);


#endif //GRAPHICS2D_DRAWPOLYGON_H
