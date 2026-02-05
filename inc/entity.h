#pragma once
#include <string.h>
#include <cglm/cglm.h>
#include <loadshaders.h>
#include <loadModel.h>
#include <camera.h>
#include <glad/glad.h>

typedef unsigned int uint;

typedef struct{
	char* nameid;
	uint vao,vbo,normalbuffer,uvbuffer,matriz,view,model,light,vertexbuffer,program;
	uint color_out;
	mat4 MVP,ModelMatrix,ViewMatrix;
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	vec3 color;
	Vector *vertices;
	Vector *uvs;
	Vector *normals;
}entity;

void InitEntity(entity* ent,const char* model,const char* nameid);
void drawEntity(entity* ent);
void destroyEntity(entity* ent);

