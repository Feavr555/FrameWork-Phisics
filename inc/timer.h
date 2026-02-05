#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL3/SDL.h>

typedef unsigned int uint;
typedef struct{
	bool started;
	uint start;
	double lastTime,dtlasttime;
	int nbFrame;
	int b;
	int countFPS;
}timer;


void init_timer(timer *t);
void limit_fps_start(timer *t);
void fps(timer *timer,SDL_Window *window);
double getDeltaTime(timer *timer);
void limit_fps_end(timer *timer);
