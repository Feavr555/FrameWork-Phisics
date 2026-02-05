#include <init.h>
#include <entitymanager.h>
#include <simulator.h>

bool game(Init_App *app,mainInit_ptr ptr_init,mainLoop_ptr ptr_loop);

int main()
{
	Init_App app;
	Init(&app,"game");
	game(&app,mainInit,mainLoop);
	destroy(&app);
	return 0;
}


