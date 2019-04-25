#ifndef LineH
#define LineH
#include <SDL.h>
void DDA_Line(int x1, int y1, int x2, int y2, SDL_Renderer *ren);
void Bresenham_Line(int x1, int y1, int x2, int y2, SDL_Renderer *ren);
void Midpoint_Line(int x1, int y1, int x2, int y2, SDL_Renderer *ren);
void LineAxis(int x1, int y1, int x2, int y2, int dx, int dy, SDL_Renderer *ren);
#endif
