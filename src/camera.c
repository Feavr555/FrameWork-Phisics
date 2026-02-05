#include <camera.h>

mat4 viewMatrix;
mat4 projectionMatrix;


void getViewMatrix(mat4 outViewMatrix)
{
	memcpy(outViewMatrix,viewMatrix,sizeof(mat4));
}

void getProjectionMatrix(mat4 outProjectionMatrix)
{
	memcpy(outProjectionMatrix,projectionMatrix,sizeof(mat4));
}

vec3 positionCamera = (vec3){ 0.f,0.f,5.f };
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speedCamera = 3.0f;
float mouseSpeed = 0.005f;


void computeMatricesFromInputs()
{
	static Uint64 lastTime = 0;
	if(!lastTime) lastTime = SDL_GetPerformanceCounter();

	Uint64 currentTime = SDL_GetPerformanceCounter();
	float deltaTime = (float)((double)(currentTime-lastTime)/SDL_GetPerformanceFrequency());
	lastTime = currentTime;
	//static float smoothDt = 1.0f/60.0f;
	//float rawDt = (float)((double)(currentTime-lastTime)/SDL_GetPerformanceFrequency());
	//lastTime = currentTime;
	//smoothDt = smoothDt * 0.9f + rawDt * 0.1f;
	//float deltaTime = smoothDt;
	
	float dx=0.0f,dy=0.0f;
	SDL_GetRelativeMouseState(&dx,&dy);
	//SDL_GetMouseState(&dx,&dy);

	//horizontalAngle += mouseSpeed * (640/2 - xpos);
	//verticalAngle += mouseSpeed * (360/2 - ypos);
	static float smoothx = 0.0f, smoothy = 0.0f;
	smoothx = smoothx * 0.7f + dx * 0.3f;
	smoothy = smoothy * 0.7f + dy * 0.3f;

	float factorCamera = mouseSpeed * deltaTime * 60.0f;
	//if(smoothx > 10.f) smoothx = 10.f;
	//if(smoothx < -10.f) smoothx = -10.f;
	//if(smoothy > 10.f) smoothy = 10.f;
	//if(smoothy < -10.f) smoothy = -10.f;

	horizontalAngle += smoothx * factorCamera;
	verticalAngle += smoothy * factorCamera;

	if(verticalAngle > GLM_PI_2f - 0.01f) verticalAngle = GLM_PI_2f - 0.01f;
	if(horizontalAngle < -GLM_PI_2f + 0.01f) horizontalAngle = GLM_PI_2f + 0.01f;

	vec3 directionCamera = {
		cosf(verticalAngle)*sinf(horizontalAngle),
		sinf(verticalAngle),
		cosf(verticalAngle)*cosf(horizontalAngle)
	};

	vec3 rightCamera = {
		sinf(horizontalAngle - GLM_PI_2f),
		0.0f,
		cosf(horizontalAngle - GLM_PI_2f)
	};
	vec3 upCamera;
	glm_vec3_cross(rightCamera,directionCamera,upCamera);

	const bool* keys = SDL_GetKeyboardState(NULL);

	if(keys[SDL_SCANCODE_W]) glm_vec3_muladds(directionCamera,deltaTime*speedCamera,positionCamera);
	if(keys[SDL_SCANCODE_S]) glm_vec3_muladds(directionCamera,-deltaTime*speedCamera,positionCamera);
	if(keys[SDL_SCANCODE_D]) glm_vec3_muladds(rightCamera,deltaTime*speedCamera,positionCamera);
	if(keys[SDL_SCANCODE_A]) glm_vec3_muladds(rightCamera,-deltaTime*speedCamera,positionCamera);
	if(keys[SDL_SCANCODE_SPACE]) glm_vec3_muladds(upCamera,deltaTime*speedCamera,positionCamera);
	if(keys[SDL_SCANCODE_LSHIFT]) glm_vec3_muladds(upCamera,-deltaTime*speedCamera,positionCamera);

	float Fov = initialFoV;
	glm_perspective(glm_rad(Fov),4.0f/3.0f,0.1f,100.0f,projectionMatrix);
	vec3 target;
	glm_vec3_add(positionCamera,directionCamera,target);
	glm_lookat(positionCamera,target,upCamera,viewMatrix);
}

