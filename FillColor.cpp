#include "FillColor.h"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

#define INT_SIZE sizeof(Uint32) * 8 /* Integer size in bits */

int findHighestBitSet(Uint32 num)
{
	int order = 0, i;

	/* Iterate over each bit of integer */
	for (i = 0; i<INT_SIZE; i++)
	{
		/* If current bit is set */
		if ((num >> i) & 1)
			order = i;
	}

	return order;
}

//Get color of a pixel
SDL_Color getPixelColor(Uint32 pixel_format, Uint32 pixel)
{
	SDL_PixelFormat* fmt = SDL_AllocFormat(pixel_format);

	Uint32 temp;
	Uint8 red, green, blue, alpha;

	//Check if pixel is a 32-bit integer
	if (findHighestBitSet(pixel) == 31)
	{
		/* Get Alpha component */
		temp = pixel & fmt->Amask;  /* Isolate alpha component */
		temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
		temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
		alpha = (Uint8)temp;
	}
	else {
		alpha = 255;
	}

	/* Get Red component */
	temp = pixel & fmt->Rmask;  /* Isolate red component */
	temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
	red = (Uint8)temp;

	/* Get Green component */
	temp = pixel & fmt->Gmask;  /* Isolate green component */
	temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
	green = (Uint8)temp;

	/* Get Blue component */
	temp = pixel & fmt->Bmask;  /* Isolate blue component */
	temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
	blue = (Uint8)temp;


	SDL_Color color = { red, green, blue, alpha };
	return color;

}

//Get all pixels on the window
SDL_Surface* getPixels(SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;
	infoSurface = SDL_GetWindowSurface(SDLWindow);
	if (infoSurface == NULL) {
		std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
		return NULL;
	}
	else {
		unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == 0) {
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
			return NULL;
		}
		else {
			if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
				return NULL;
			}
			else {
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
			}
		}
	}
	return saveSurface;
}

//Compare two colors
bool compareTwoColors(SDL_Color color1, SDL_Color color2)
{
	if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a)
		return true;
	return false;
}


bool canFilled(SDL_Window *win, Vector2D newPoint, Uint32 pixel_format,
	SDL_Renderer *ren, SDL_Color fillColor, SDL_Color boundaryColor)
{
	SDL_Surface *surface = getPixels(win, ren);

	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;
	int w = surface->w;

	int index = newPoint.y * w + newPoint.x;
	Uint32 pixel = pixels[index];
	SDL_Color color = getPixelColor(pixel_format, pixel);
	cout << (int)color.r << "," << (int)color.g << "," << (int)color.b << "," << (int)color.a << endl;

	if (!compareTwoColors(color, fillColor) && !compareTwoColors(color, boundaryColor))
	{
		return true;
	}

	return false;
}


void BoundaryFill4(SDL_Window *win, Vector2D startPoint, Uint32 pixel_format,
	SDL_Renderer *ren, SDL_Color fillColor, SDL_Color boundaryColor)
{
	stack<Vector2D> box;
	box.push(Vector2D(startPoint));
	while (!box.empty())
	{
		SDL_RenderDrawPoint(ren, box.top().x, box.top().y);
		Vector2D point = box.top();
		point.x = box.top().x - 1;
		if (canFilled(win, point, pixel_format, ren, fillColor, boundaryColor))
		{
			box.push(Vector2D(point));
			continue;
		}
		point.x = box.top().x + 1;
		if (canFilled(win, point, pixel_format, ren, fillColor, boundaryColor))
		{
			box.push(Vector2D(point));
			continue;
		}
		point.y = box.top().y - 1;
		if (canFilled(win, point, pixel_format, ren, fillColor, boundaryColor))
		{
			box.push(Vector2D(point));
			continue;
		}
		point.y = box.top().y + 1;
		if (canFilled(win, point, pixel_format, ren, fillColor, boundaryColor))
		{
			box.push(Vector2D(point));
			continue;
		}
		SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
		box.pop();
	}

}

//======================================================================================================================
//=============================================FILLING TRIANGLE=========================================================

int maxIn3(int a, int b, int c)
{
	int max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return max;
}

int minIn3(int a, int b, int c)
{
	int min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return min;
}

void swap(Vector2D &a, Vector2D &b)
{
	Vector2D temp(a);
	a.set(b);
	b.set(temp);

}

void ascendingSort(Vector2D &v1, Vector2D &v2, Vector2D &v3)
{
	/*if (v1.y > v2.y) {
	swap(v1.x, v2.x);
	swap(v1.y, v2.y);
	}
	if (v1.y > v3.y) {
	swap(v1.x, v3.x);
	swap(v1.y, v3.y);
	}
	if (v2.y > v3.y) {
	swap(v2.x, v3.x);
	swap(v2.y, v3.y);
	}*/

	if (v1.y > v2.y) {
		swap(v1, v2);
	}

	if (v1.y > v3.y)
	{
		swap(v1, v3);
	}

	if (v2.y > v3.y)
	{
		swap(v2, v3);
	}


}

void TriangleFill1(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
	int Min = minIn3(v1.x, v2.x, v3.x);
	int Max = maxIn3(v1.x, v2.x, v3.x);
	Bresenham_Line(Min, v1.y, Max, v1.y, ren);
}

void TriangleFill2(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
	float a = (float)(v3.x - v1.x) / (v3.y - v1.y);
	float b = (float)(v3.x - v2.x) / (v3.y - v2.y);
	float X_LEFT = v1.x;
	float X_RIGHT = v2.x;
	for (int i = v1.y; i <= v3.y; i++)
	{
		X_LEFT += a;
		X_RIGHT += b;
		Bresenham_Line(int(X_LEFT + 0.5), i, int(X_RIGHT + 0.5), i, ren);
	}
}

void TriangleFill3(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
	float a = (float)(v2.x - v1.x) / (v2.y - v1.y);
	float b = (float)(v3.x - v1.x) / (v3.y - v1.y);
	float X_LEFT = v1.x;
	float X_RIGHT = v1.x;
	for (int i = v1.y; i <= v3.y; i++)
	{
		X_LEFT += a;
		X_RIGHT += b;
		Bresenham_Line(int(X_LEFT + 0.5), i, int(X_RIGHT + 0.5), i, ren);
	}
}

void TriangleFill4(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
	Vector2D v4;
	v4.y = v2.y;
	float b = (float)(v3.x - v1.x) / (v3.y - v1.y);
	v4.x = v1.x + int((v2.y - v1.y)*b + 0.5);
	TriangleFill1(v2, v2, v4, ren, fillColor);
	TriangleFill2(v4, v2, v3, ren, fillColor);
	TriangleFill3(v1, v2, v4, ren, fillColor);
}

void TriangleFill(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
	ascendingSort(v1, v2, v3);
	SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	if (v1.y == v2.y && v2.y == v3.y) {
		TriangleFill1(v1, v2, v3, ren, fillColor);
		return;
	}
	if (v1.y == v2.y && v2.y < v3.y) {
		TriangleFill2(v1, v2, v3, ren, fillColor);
		return;
	}
	if (v1.y < v2.y && v3.y == v2.y) {
		TriangleFill3(v1, v2, v3, ren, fillColor);
		return;
	}
	if (v1.y < v2.y && v2.y < v3.y) {
		TriangleFill4(v1, v2, v3, ren, fillColor);
		return;
	}
	return;
}
//======================================================================================================================
//===================================CIRCLE - RECTANGLE - ELLIPSE=======================================================
bool isInsideCircle(int xc, int yc, int R, int x, int y)
{
	if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= R * R) {
		return 1;
	}
	return 0;
}

void FillIntersection(int x1, int y1, int x2, int y2, int xc, int yc, int R,
	SDL_Renderer *ren, SDL_Color fillColor)
{
	int Min = minIn3(x1, x2, INT_MAX);
	int Max = maxIn3(x1, x2, INT_MIN);
	for (int i = Min; i <= Max; i++)
	{
		if (isInsideCircle(xc, yc, R, i, y1) == 1) {
			SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
			SDL_RenderDrawPoint(ren, i, y1);
		}
	}
}

void FillIntersectionRectangleCircle(Vector2D vTopLeft, Vector2D vBottomRight, int xc, int yc, int R,
	SDL_Renderer *ren, SDL_Color fillColor)
{
	for (int y = vTopLeft.y; y <= vBottomRight.y; y++)
	{
		FillIntersection(vTopLeft.x, y, vBottomRight.x, y, xc, yc, R, ren, fillColor);
	}
}

void RectangleFill(Vector2D vTopLeft, Vector2D vBottomRight, SDL_Renderer *ren, SDL_Color fillColor)
{
	for (int y = vTopLeft.y; y <= vBottomRight.y; y++)
	{
		DDA_Line(vTopLeft.x, y, vBottomRight.x, y, ren);
	}
}

void put4line(int xc, int yc, int x, int y, SDL_Renderer *ren, SDL_Color fillColor)
{
	SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_RenderDrawPoint(ren, x, y);
	DDA_Line(xc + x, yc + y, xc - x, yc + y, ren);
	DDA_Line(xc + y, yc + x, xc - y, yc + x, ren);
	DDA_Line(xc + y, yc - x, xc - y, yc - x, ren);
	DDA_Line(xc + x, yc - y, xc - x, yc - y, ren);
}

void CircleFill(int xc, int yc, int R, SDL_Renderer *ren, SDL_Color fillColor)
{
	int x = 0;
	int p = 1 - R;
	put4line(xc, yc, x, R, ren, fillColor);
	while (x < R)
	{
		if (p < 0) p += 2 * x + 3;
		else {
			p += 2 * (x - R) + 5;
			R--;
		}
		x++;
		put4line(xc, yc, x, R, ren, fillColor);
	}
}

bool IsInside(int xc, int yc, int a, int b, int x, int y)
{
	float c = (float)(x - xc)*(x - xc) / (a*a);
	float d = (float)(y - yc)*(y - yc) / (b*b);
	float kq = c + d;
	if (kq <= 1)
		return 1;
	return 0;
}
void FillIntersection1(int x1, int y1, int x2, int y2, SDL_Renderer *ren, SDL_Color fillColor, int xe, int ye, int a, int b)
{
	int Min = minIn3(x1, x2, INT_MAX);
	int Max = maxIn3(x1, x2, INT_MIN);
	for (int i = Min; i <= Max; i++)
		if (IsInside(xe, ye, a, b, i, y1) == 1)
			SDL_RenderDrawPoint(ren, i, y1);
} 

void Put4LineEllipseCircle(int xc, int yc, int x, int y, SDL_Renderer *ren, SDL_Color fillColor, int xe, int ye, int a, int b)
{
	FillIntersection1(xc + x, yc + y, xc - x, yc + y, ren, fillColor, xe, ye, a, b);
	FillIntersection1(xc + y, yc + x, xc - y, yc + x, ren, fillColor, xe, ye, a, b);
	FillIntersection1(xc + y, yc - x, xc - y, yc - x, ren, fillColor, xe, ye, a, b);
	FillIntersection1(xc + x, yc - y, xc - x, yc - y, ren, fillColor, xe, ye, a, b);
}


void FillIntersectionEllipseCircle(int xcE, int ycE, int a, int b, int xc, int yc, int R,
	SDL_Renderer *ren, SDL_Color fillColor)
{
	int x = 0;
	int p = 1 - R;
	Put4LineEllipseCircle(xc, yc, x, R, ren, fillColor, xcE, ycE, a, b);
	while (x < R)
	{
		if (p < 0) p += 2 * x + 3;
		else {
			p += 2 * (x - R) + 5;
			R--;
		}
		x++;
		Put4LineEllipseCircle(xc, yc, x, R, ren, fillColor, xcE, ycE, a, b);
	}
}
void Put4LineTwoCircles(int xc, int yc, int x, int y, int xc2, int yc2, int R2,
	SDL_Renderer *ren, SDL_Color fillColor)
{
	FillIntersection(xc + x, yc + y, xc - x, yc + y, xc2, yc2, R2, ren, fillColor);
	FillIntersection(xc + y, yc + x, xc - y, yc + x, xc2, yc2, R2, ren, fillColor);
	FillIntersection(xc + y, yc - x, xc - y, yc - x, xc2, yc2, R2, ren, fillColor);
	FillIntersection(xc + x, yc - y, xc - x, yc - y, xc2, yc2, R2, ren, fillColor);
}
void FillIntersectionTwoCircles(int xc1, int yc1, int R1, int xc2, int yc2, int R2,
	SDL_Renderer *ren, SDL_Color fillColor)
{
	int x = 0;
	int p = 1 - R1;
	Put4LineTwoCircles(xc1, yc1, x, R1, xc2, yc2, R2, ren, fillColor);
	while (x < R1)
	{
		if (p < 0) p += 2 * x + 3;
		else {
			p += 2 * (x - R1) + 5;
			R1--;
		}
		x++;
		Put4LineTwoCircles(xc1, yc1, x, R1, xc2, yc2, R2, ren, fillColor);
	}
}
//==============================================