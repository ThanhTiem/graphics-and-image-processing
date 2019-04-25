#include "Circle.h"

void Draw8Points(int xc, int yc, int x, int y, SDL_Renderer *ren)
{
	int new_x;
	int new_y;
	//1
	new_x = xc + x;
	new_y = yc + y;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//2
	new_x = xc + y;
	new_y = yc + x;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//3
	new_x = xc - x;
	new_y = yc - y;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//4
	new_x = xc - y;
	new_y = yc - x;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//5
	new_x = xc - x;
	new_y = yc + y;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//6
	new_x = xc + x;
	new_y = yc - y;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//7
	new_x = xc - y;
	new_y = yc + x;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//8
	new_x = xc + y;
	new_y = yc - x;
	SDL_RenderDrawPoint(ren, new_x, new_y);


}

void BresenhamDrawCircle(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x = R; int y = 0;
	int p = 3 - 2 * R;
	Draw8Points(xc, yc, x, y, ren);
	while (x >y)
	{
		
		if (p<=0) p = p + 4 * y + 6;
		else
		{
			p = p + 4 * (y-x) + 10;
			x--;
		}
		y = y + 1;
		Draw8Points(xc, yc, x, y, ren);
	}
}

void MidpointDrawCircle(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x, y, p;
	x = R;
	y = 0;
	p = 1 - R;
	Draw8Points(xc, yc, x, y, ren);
	while (x > y)
	{
		if (p <= 0) {
			p += 2 * y +3;
		}
		else {
			p += 2 * y - 2 * x + 5;
			x--;

		}
		y++;
		Draw8Points(xc, yc, x, y, ren);
	}
}
