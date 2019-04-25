#include "Bezier.h"
#include <iostream>
using namespace std;

void DrawCurve2(SDL_Renderer *ren, Vector2D p1, Vector2D p2, Vector2D p3)
{
	float t;

	float x, y;
	for (t = 0; t <= 1; t = t + 0.001)
	{
		 x = (1 - t)*(1 - t)*p1.x + 2 * (1 - t)*t*p2.x + t * t*p3.x;
		 y = (1 - t)*(1 - t)*p1.y + 2 * (1 - t)*t*p2.y + t * t*p3.y;
		SDL_RenderDrawPoint(ren, (int)0.5 + x, (int)0.5 + y);

	}
	
}
void DrawCurve3(SDL_Renderer *ren, Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4)
{
	
	float t;
	float x, y;
	for (t = 0; t <= 1; t += 0.001)
	{
		x = (1 - t)*(1 - t)*(1 - t)*p1.x + 3 * (1 - t)*(1 - t)*t*p2.x + 3 * (1 - t)*t*t*p3.x + t * t*t*p4.x;
		y = (1 - t)*(1 - t)*(1 - t)*p1.y + 3 * (1 - t)*(1 - t)*t*p2.y + 3 * (1 - t)*t*t*p3.y + t * t*t*p4.y;
		SDL_RenderDrawPoint(ren, (int)0.5 + x, (int)0.5 + y);
	}
}
