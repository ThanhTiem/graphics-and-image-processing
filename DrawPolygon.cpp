#include "DrawPolygon.h"
#include "Line.h"
#include <iostream>
#include <cmath>
//#define PI 3.1412
using namespace std;

void DrawEquilateralTriangle(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x[3], y[3];
	float phi = M_PI / 2;
	for (int i = 0; i < 3; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		phi += 2 * M_PI / 3;
	}
	
	for (int i = 0; i < 3; i++)
	{	
		Bresenham_Line(x[i], y[i], x[(i + 1) % 3], y[(i + 1) % 3], ren);
	}
}

void DrawSquare(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x[4], y[4];
	float phi =M_PI/2;
	for (int i = 0; i < 4; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		phi += 2 * M_PI / 4;
	}

	for (int i = 0; i < 4; i++)
	{
		DDA_Line(x[i], y[i], x[(i + 1) % 4], y[(i + 1) % 4], ren);
	}
}
void DrawPentagon(int xc, int yc, int R, SDL_Renderer *ren)
{

	int x[5], y[5];
	float phi = M_PI / 2;
	for (int i = 0; i < 5; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		phi += 2 * M_PI / 5;
	}

	for (int i = 0; i < 5; i++)
	{
		Bresenham_Line(x[i], y[i], x[(i + 1) % 5], y[(i + 1) % 5], ren);
	}
}
void DrawHexagon(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x[6], y[6];
	float phi = 0;
	for (int i = 0; i < 6; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		phi += 2 * M_PI / 6;
	}

	for (int i = 0; i < 6; i++)
	{
		Bresenham_Line(x[i], y[i], x[(i + 1) % 6], y[(i + 1) % 6], ren);
	}
}

void DrawStar(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x[5];
	int y[5];
	float phi = M_PI / 2;
	for (int i = 0; i < 5; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		phi += 2 * M_PI / 5;
	}
	
	for (int i = 0; i < 5; i++)
	{
		Bresenham_Line(x[i], y[i], x[(i + 2) % 5], y[(i + 2) % 5], ren);
	}
}

void DrawEmptyStar(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x[5], xp[5];
	int y[5], yp[5];
	float phi = M_PI / 2;
	float r = R * sin(M_PI / 10) / sin(7 * M_PI / 10);
	for (int i = 0; i < 5; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		xp[i] = xc + int(r*cos(phi + M_PI / 5) + 0.5);
		yp[i] = yc - int(r*sin(phi + M_PI / 5) + 0.5);
		phi += 2 * M_PI / 5;
	}

	for (int i = 0; i < 5; i++)
	{
		Bresenham_Line(x[i], y[i], xp[i], yp[i], ren);
		Bresenham_Line(xp[i], yp[i], x[(i + 1) % 5], y[(i + 1) % 5], ren);
	}
}

//Star with eight wings
void DrawStarEight(int xc, int yc, int R, SDL_Renderer *ren)
{
	int x[8], xp[8];
	int y[8], yp[8];
	float phi = 0;
	float r = R * sin(M_PI / 8) / sin(6 * M_PI / 8);
	for (int i = 0; i < 8; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		xp[i] = xc + int(r*cos(phi + M_PI / 8) + 0.5);
		yp[i] = yc - int(r*sin(phi + M_PI / 8) + 0.5);
		phi += 2 * M_PI / 8;
	}

	for (int i = 0; i < 8; i++)
	{
		Bresenham_Line(x[i], y[i], xp[i], yp[i], ren);
		Bresenham_Line(xp[i], yp[i], x[(i + 1) % 8], y[(i + 1) % 8], ren);
	}
}

//For drawing one star of convergent star
void DrawStarAngle(int xc, int yc, int R, float startAngle, SDL_Renderer *ren)
{
	int x[5], xp[5];
	int y[5], yp[5];
	float phi = startAngle;
	float r = R * sin(M_PI / 10) / sin(7 * M_PI / 10);
	for (int i = 0; i < 5; i++)
	{
		x[i] = xc + int(R*cos(phi) + 0.5);
		y[i] = yc - int(R*sin(phi) + 0.5);
		xp[i] = xc + int(r*cos(phi + M_PI / 5) + 0.5);
		yp[i] = yc - int(r*sin(phi + M_PI / 5) + 0.5);
		phi += 2 * M_PI / 5;
	}

	for (int i = 0; i < 5; i++)
	{
		Bresenham_Line(x[i], y[i], xp[i], yp[i], ren);
		Bresenham_Line(xp[i], yp[i], x[(i + 1) % 5], y[(i + 1) % 5], ren);
	}
}

void DrawConvergentStar(int xc, int yc, int r, SDL_Renderer *ren)
{
	int BanKinh = r;
	float phi = M_PI / 2;
	while (BanKinh > 1) {
		DrawStarAngle(xc, yc, int(BanKinh + 0.5), phi, ren);
		phi = phi + M_PI;
		BanKinh = BanKinh * sin(M_PI / 10) / sin(7 * M_PI / 10);
	}
}
