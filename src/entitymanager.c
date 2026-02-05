#include <entitymanager.h>


void Init_EntityManager(entitymanager* man)
{
	man->entities = Vector_init(sizeof(entity));
}

void createEntity(entitymanager* man,const char*const model,const char*const nameentity)
{
	entity ent;
	InitEntity(&ent,model,nameentity);
	Vector_pushback(man->entities,&ent);
}

void moveEntity(entitymanager* man,vec3 position)
{
	entity* ent = man->entities->data;
	//ent->position = { 1,1,1 };
}

void drawEntities(entitymanager* man)
{
	//for(uint i=0; i<man->entities->size; ++i)
	//	drawEntity(Vector_getValue(man->entities,i));

	entity* ent = man->entities->data;
	computeMatricesFromInputs();
	for(uint i=0; i<man->entities->size; ++i){
		drawEntity(ent);
		ent++;
	}
}

void destroyEntityManager(entitymanager *man)
{
	entity* ents = man->entities->data;
	for(uint i=0; i<man->entities->size; ++i){
		destroyEntity(ents);
		ents++;
	}
	Vector_destroy(man->entities);
}
