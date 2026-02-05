#include <timer.h>

// first call
void init_timer(timer *timer)
{
	timer->started = 0;
	timer->start = 0;
	timer->lastTime = 0;
	timer->dtlasttime = 0;
	timer->nbFrame = 0;
	timer->b = SDL_GetTicks();
	timer->countFPS = 60;

	uint start_time = SDL_GetPerformanceCounter();
	uint frequency = SDL_GetPerformanceFrequency();
	timer->lastTime = (double)start_time/(double)frequency;
	timer->dtlasttime = timer->lastTime;
	timer->start = 0;
	timer->started = false;

}
double getTime()
{
	uint start_time = SDL_GetPerformanceCounter();
	uint frequency = SDL_GetPerformanceFrequency();
	return (double)start_time/(double)frequency;
}

// draw fps - second call
void fps(timer *timer,SDL_Window *window)
{
	double currentTime = getTime();
	timer->nbFrame++;
	if(currentTime - timer->lastTime >= 1.0){
		double ms = 1000.0/(double)(timer->nbFrame);
		//double frames = 1.0f/(ms/1000.0f);
		double frames = (double)timer->nbFrame;
		char title[256];
		sprintf(title,"OpenGL - %.4f ms/Frame - %d fps",ms,(uint)frames);
		SDL_SetWindowTitle(window,title);
		timer->nbFrame = 0;
		timer->lastTime += 1.0;
	}
}

// thrid call - then glClearColor and glClear
double getDeltaTime(timer *timer)
{
	double currentTime = getTime();
	double dt = currentTime - timer->dtlasttime;
	timer->dtlasttime = currentTime;
	return dt;
}
double getTicks(timer *timer)
{
	uint _time = 0;
	if(timer->started){
		_time = SDL_GetTicks() - timer->start;
	}
	return _time;
}
// first call then init_timer
void limit_fps_start(timer *timer)
{
	timer->started = true;
	timer->start = SDL_GetTicks();
}
// four call - then SDL_GL_SwapWindow

void limit_fps_end(timer *timer)
{
	int limit = timer->countFPS;
	int frame = getTicks(timer);
	if(frame < (1000/limit)){
		SDL_Delay((1000/limit)-frame);
	}
}



