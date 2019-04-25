#ifndef GRAPHICS2D_FILLCOLOR_H
#define GRAPHICS2D_FILLCOLOR_H

#include <SDL.h>
#include "Vector2D.h"
#include "Line.h"

void BoundaryFill4(SDL_Window *win, Vector2D startPoint, Uint32 pixel_format,
	SDL_Renderer *ren, SDL_Color fillColor, SDL_Color boundaryColor);
void TriangleFill(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor);
void CircleFill(int xc, int yc, int R, SDL_Renderer *ren, SDL_Color fillColor);
void RectangleFill(Vector2D vTopLeft, Vector2D vBottomRight, SDL_Renderer *ren, SDL_Color fillColor);
void FillIntersectionRectangleCircle(Vector2D vTopLeft, Vector2D vBottomRight, int xc, int yc, int R, SDL_Renderer *ren, SDL_Color fillColor);
void FillIntersectionEllipseCircle(int xcE, int ycE, int a, int b, int xc, int yc, int R, SDL_Renderer *ren, SDL_Color fillColor);
void FillIntersectionTwoCircles(int xc1, int yc1, int R1, int xc2, int yc2, int R2, SDL_Renderer *ren, SDL_Color fillColor);


#endif
