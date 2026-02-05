#include <init.h>

bool Init(Init_App *app,const char*title)
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	app->window = SDL_CreateWindow(title,WIDTH,HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	app->context = SDL_GL_CreateContext(app->window);
	SDL_GL_SetSwapInterval(0);
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	app->finish = false;
	SDL_PumpEvents();
	SDL_SetWindowMouseGrab(app->window,true);
	SDL_SetWindowRelativeMouseMode(app->window, true);
}

bool destroy(Init_App *app)
{
	SDL_SetWindowRelativeMouseMode(app->window, false);
	SDL_Quit();
	SDL_DestroyWindow(app->window);
}

typedef void (*mainInit_ptr)(entitymanager*);
typedef void (*mainLoop_ptr)(entitymanager*);

bool game(Init_App *app,mainInit_ptr ptr_init,mainLoop_ptr ptr_loop)
{
	timer t;
	init_timer(&t);
	glClearColor(0,1,1,1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	entitymanager man;
	Init_EntityManager(&man);
	ptr_init(&man);
	//createEntity(&man,"monkey.obj",NULL);
	//createEntity(&man,"sphere.obj",NULL);
	//entity* ent = man.entities->data;
	//ent->position[0] = 0;
	//ent->position[1] = 0;
	//ent->position[2] = 0;
	//createEntity(&man,"sphere.obj");

	t.countFPS = 120;
	while(!app->finish){
		limit_fps_start(&t);
		if(SDL_PollEvent(&app->e)){
			if(app->e.type == SDL_EVENT_QUIT) app->finish = true;
		}
		const bool *keystates = SDL_GetKeyboardState(NULL);
		if(keystates[SDL_SCANCODE_ESCAPE]) app->finish = true;

		fps(&t,app->window);

		glClearColor(0.05f,0.05f,0.05f,0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double dt = getDeltaTime(&t);

		// TODO:
		// EntityManager (Entities, renderer)
		// SystemManager (physics)
		ptr_loop(&man);
		drawEntities(&man);

		SDL_GL_SwapWindow(app->window);
		limit_fps_end(&t);
	}
	destroyEntityManager(&man);
}

