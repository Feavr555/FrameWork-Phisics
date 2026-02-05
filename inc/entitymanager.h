#pragma once
#include <vector.h>
#include <entity.h>
#include <cglm/cglm.h>

typedef struct{
	Vector *entities;
}entitymanager;

void Init_EntityManager(entitymanager* man);
void createEntity(entitymanager* man,const char*const model,const char*const nameentity);
void drawEntities(entitymanager* man);
void destroyEntityManager(entitymanager* man);
void moveEntity(entitymanager* man, vec3 position);
