// Life.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <Windows.h>


int oldfield[500][500];
int newfield[500][500];
//Generates random numbers
double decrandom(){
	double ran; 
	ran = (float) rand()/RAND_MAX;
	return ran;
}
//Generates random numbers from 0 to 1
int binrandom(){
	int ran;
	ran = rand();
	if (ran % 2 == 0){
		ran = 1;
	}
	else {
		ran = 0;
	}
	return ran;
}

//Initializes field of cells using random numbers provided by binrandom()
void fieldStp(){
	int x, y;
	int field[500][500];
	for (x = 0; x <= 499; x = x + 1){
		for (y = 0; y <= 499; y = y + 1){
			field[x][y] = binrandom();
			oldfield[x][y] = field[x][y];
		}
	}
}

//Sets all cells to their new state
void fieldref(){
	int sum;
	for (int x = 0; x <= 499; x = x + 1){
		for (int y = 0; y <= 499; y = y + 1){
			sum = oldfield[x + 1][y] + oldfield[x - 1][y] + oldfield[x][y + 1] + oldfield[x][y - 1] + oldfield[x + 1][y + 1] + oldfield[x - 1][y + 1] + oldfield[x - 1][y - 1] + oldfield[x + 1][y - 1];
			//This is where rules are applied 
			if (sum >3 || sum < 2){
				newfield[x][y] = 0;
			}
			if (sum == 3){
				newfield[x][y] = 1;


			}
			if ((sum == 2 || sum == 3) && oldfield[x][y] == 1){
				newfield[x][y] = oldfield[x][y];
			}
			//This is where rule part ends
		}
	}

	for (int x = 0; x <= 499; x = x + 1){
		for (int y = 0; y <= 499; y = y + 1){
			oldfield[x][y] = newfield[x][y];
		}
	}
	
}
int main(int argc, char **argv){
	bool quit = false;
	fieldStp();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("Life", 100, 100, 1000, 1000, SDL_WINDOW_SHOWN);
	if (window == NULL){
		printf("ERROR Window creation failed");
		return 0;
	}
	SDL_Renderer* renderer = NULL;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event* mainEvent = new SDL_Event();
	SDL_Texture* replicator = NULL;
	replicator = IMG_LoadTexture(renderer, "replicator.jpg");
	SDL_Texture* dead = NULL;
	dead = IMG_LoadTexture(renderer, "dead.jpg");
	SDL_Rect replicator_rect;
	SDL_Rect dead_rect;
	while (quit == false && mainEvent->type != SDL_QUIT){
		int x, y;

		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);
		fieldref();

		for (x = 0; x <= 499; x = x + 1){
			for (y = 0; y <= 499; y = y + 1){
				if (oldfield[x][y] == 1){
					replicator_rect.x = 2 * x;
					replicator_rect.y = 2 * y;
					replicator_rect.w = 2;
					replicator_rect.h = 2;
					SDL_RenderCopy(renderer, replicator, NULL, &replicator_rect);
				}
			}
		}

		SDL_RenderPresent(renderer);
		Sleep(20);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
	return 0;
}