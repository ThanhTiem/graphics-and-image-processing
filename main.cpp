#include <iostream>
#include <SDL.h>
#include "Bezier.h"


using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;



SDL_Event event;


int main(int, char**) {
	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	//Make sure creating our window went ok
	if (win == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create a renderer that will draw to the window, -1 specifies that we want to load whichever
	//DON'T FORGET CHANGE THIS LINE IN YOUR SOURCE ----->>>>> SDL_RENDERER_SOFTWARE

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	if (ren == NULL) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	//YOU CAN INSERT CODE FOR TESTING HERE

	Vector2D p1(22, 215), p2(94, 43), p3(140, 258), p4(213, 150);


	SDL_Rect *rect1 = new SDL_Rect();
	rect1->x = p1.x - 3;
	rect1->y = p1.y - 3;
	rect1->w = 6;
	rect1->h = 6;

	SDL_Rect *rect2 = new SDL_Rect();
	rect2->x = p2.x - 3;
	rect2->y = p2.y - 3;
	rect2->w = 6;
	rect2->h = 6;

	SDL_Rect *rect3 = new SDL_Rect();
	rect3->x = p3.x - 3;
	rect3->y = p3.y - 3;
	rect3->w = 6;
	rect3->h = 6;

	SDL_Rect *rect4 = new SDL_Rect();
	rect4->x = p4.x - 3;
	rect4->y = p4.y - 3;
	rect4->w = 6;
	rect4->h = 6;

	SDL_Color colorCurve = { 100, 20, 40, 255 }, colorRect = { 0, 255, 40, 255 };


	SDL_RenderPresent(ren);

	//Take a quick break after all that hard work
	//Quit if happen QUIT event
	bool running = true;
	Vector2D *p = NULL;
	SDL_Rect *rect = NULL;
	while (running)
	{
		//If there's events to handle
		if (SDL_PollEvent(&event))
		{
			//HANDLE MOUSE EVENTS!!!

			pair<int, int> MouseDown;
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				MouseDown = { x, y };

				//Check MouseDown is on which point
				if ((int(rect1->x) <= MouseDown.first) && (MouseDown.first <= int(rect1->x + rect1->w)))
					if ((int(rect1->y) <= MouseDown.second) && (MouseDown.second <= int(rect1->y + rect1->h)))
						p = &p1, rect = rect1;
				if ((int(rect2->x) <= MouseDown.first) && (MouseDown.first <= int(rect2->x + rect2->w)))
					if ((int(rect2->y) <= MouseDown.second) && (MouseDown.second <= int(rect2->y + rect2->h)))
						p = &p2, rect = rect2;
				if ((int(rect3->x) <= MouseDown.first) && (MouseDown.first <= int(rect3->x + rect3->w)))
					if ((int(rect3->y) <= MouseDown.second) && (MouseDown.second <= int(rect3->y + rect3->h)))
						p = &p3, rect = rect3;
				if ((int(rect4->x) <= MouseDown.first) && (MouseDown.first <= int(rect4->x + rect4->w)))
					if ((int(rect4->y) <= MouseDown.second) && (MouseDown.second <= int(rect4->y + rect4->h)))
						p = &p4, rect = rect4;
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				if (p != NULL)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					p->set(x*1.0, y*1.0);
					rect->x = x - 3;
					rect->y = y - 3;
					rect->w = 6;
					rect->h = 6;
				}
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				p = NULL;
			}
			//Fix position


			//Draw
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);


			SDL_SetRenderDrawColor(ren, colorCurve.r, colorCurve.g, colorCurve.b, colorCurve.a);
			DrawCurve2(ren, p1, p2, p4);
			DrawCurve3(ren, p1, p2, p3, p4);
			SDL_SetRenderDrawColor(ren, colorRect.r, colorRect.g, colorRect.b, colorRect.a);
			SDL_RenderDrawRect(ren, rect1);
			SDL_RenderDrawRect(ren, rect2);
			SDL_RenderDrawRect(ren, rect3);
			SDL_RenderDrawRect(ren, rect4);
			SDL_RenderPresent(ren);

			//If the user has Xed out the window
			if (event.type == SDL_QUIT)
			{
				//Quit the program
				running = false;
			}
		}

	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}