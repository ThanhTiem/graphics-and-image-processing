#ifndef GRAPHICS2D_BEZIER_H
#define GRAPHICS2D_BEZIER_H

#include <SDL.h>
#include "Vector2D.h"
#include <vector>

void DrawCurve2(SDL_Renderer *ren, Vector2D p1, Vector2D p2, Vector2D p3);
void DrawCurve3(SDL_Renderer *ren, Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4);

#endif //GRAPHICS2D_BEZIER_H
