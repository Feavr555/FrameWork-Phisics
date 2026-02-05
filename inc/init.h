#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <glad/glad.h>

#include <SDL3/SDL.h>
#include <timer.h>
#include <entitymanager.h>

#define WIDTH 640
#define HEIGHT 360

typedef unsigned int uint;

typedef struct{
	SDL_Window *window;
	SDL_GLContext context;
	SDL_Event e;
	bool finish;
}Init_App;

bool Init(Init_App *app,const char*title);
bool destroy(Init_App *app);



