#include "Parabol.h"

void Draw2Points(int xc, int yc, int x, int y, SDL_Renderer *ren)
{
	int new_x, new_y;
	//1
	new_x = xc + x;
	new_y = yc + y;
	SDL_RenderDrawPoint(ren, new_x, new_y);
	//2:
	new_x = xc - x;
	new_y = yc + y;
	SDL_RenderDrawPoint(ren, new_x, new_y);

}
void BresenhamDrawParapolPositive(int xc, int yc, int A, SDL_Renderer *ren)
{
	int x, y, p;
	x = 0; y = 0;
	p = 1 - A;
	Draw2Points(xc, yc, x, y, ren);
	while (x < A)
	{
		if (p <= 0) {
			p += 2 * x + 3;
		}
		else {
			y++;
			p += 2 * x + 3 - 2 * A;
		}
		x++;
		Draw2Points(xc, yc, x, y, ren);
	}
	p = 2 * A - 1;
	Draw2Points(xc, yc, x, y, ren);
	while (x<600 && y<800)
	{
		if (p <= 0) {
			p += 4 * A;
		}
		else {
			x++;
			p += 4 * A - 4 * x - 4;
		}
		y++;
		Draw2Points(xc, yc, x, y, ren);
	}
}

void BresenhamDrawParapolNegative(int xc, int yc, int A, SDL_Renderer *ren)
{
	int x, y, p;
	x = 0; y = 0;
	p = 1 - A;
	Draw2Points(xc, yc, x, y, ren);
	while (x <= A)
	{
		if (p <= 0) {
			p += 2 * x + 3;
		}
		else {
			y--;
			p += 2 * x + 3 - 2 * A;
		}
		x++;
		Draw2Points(xc, yc, x, y, ren);
	}
	p = 2 * A - 1;
	Draw2Points(xc, yc, x, y, ren);
	while (x<600 && y<800)
	{
		if (p <= 0) {
			p += 4 * A;
		}
		else {
			x++;

			p += 4 * A - 4 * x - 4;
		}
		y--;

		Draw2Points(xc, yc, x, y, ren);
	}
}
