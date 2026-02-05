#include <entity.h>



void InitEntity(entity* ent,const char* model,const char* nameid)
{
	if(nameid != NULL){
		ent->nameid = (char*)malloc(strlen(nameid)+1);
		strcpy(ent->nameid,nameid);
	}else ent->nameid = NULL;
	ent->vertices = Vector_init(sizeof(vec3));
	ent->uvs = Vector_init(sizeof(vec2));
	ent->normals = Vector_init(sizeof(vec3));
	bool res = loadOBJ(model,ent->vertices,ent->uvs,ent->normals);
	ent->color[0] = 1.f;
	ent->color[1] = 1.f;
	ent->color[2] = 1.f;

	glGenBuffers(1,&ent->vbo);
	glBindBuffer(GL_ARRAY_BUFFER,ent->vbo);

	glGenVertexArrays(1,&ent->vao);
	glBindVertexArray(ent->vao);

	glGenBuffers(1,&ent->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,ent->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,(ent->vertices->size)*sizeof(vec3),ent->vertices->data,GL_STATIC_DRAW);

	glGenBuffers(1,&ent->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,ent->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER,(ent->uvs->size)*sizeof(vec2),ent->uvs->data,GL_STATIC_DRAW);

	glGenBuffers(1,&ent->normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,ent->normalbuffer);
	glBufferData(GL_ARRAY_BUFFER,(ent->normals->size)*sizeof(vec3),ent->normals->data,GL_STATIC_DRAW);
	
	ent->program = LoadShaders("shaders/vertexlux.glsl","shaders/fragmentlux.glsl");
	ent->matriz = glGetUniformLocation(ent->program,"MVP");
	ent->view = glGetUniformLocation(ent->program,"V");
	ent->model = glGetUniformLocation(ent->program,"M");
	ent->light = glGetUniformLocation(ent->program,"LightPosition_worldspace");
	ent->color_out = glGetUniformLocation(ent->program,"color_out");
}

void position(entity* ent)
{
	mat4 projection = GLM_MAT4_IDENTITY_INIT;
	mat4 view = GLM_MAT4_IDENTITY_INIT;
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	mat4 mul = GLM_MAT4_IDENTITY_INIT;
	getProjectionMatrix(projection);
	getViewMatrix(view);
	glm_translate(model,ent->position);
	glm_scale(model,(vec3){1.f,1.f,1.f});
	glm_mul(view,model,mul);
	glm_mul(projection,mul,ent->MVP);
}

void drawEntity(entity* ent)
{
	glm_mat4_identity(ent->ModelMatrix);
	getViewMatrix(ent->ViewMatrix);
	glUseProgram(ent->program);
	position(ent);
	glUniformMatrix4fv(ent->matriz,1,GL_FALSE,&ent->MVP[0][0]);
	glUniformMatrix4fv(ent->model,1,GL_FALSE,&ent->ModelMatrix[0][0]);
	glUniformMatrix4fv(ent->view,1,GL_FALSE,&ent->ViewMatrix[0][0]);
	vec3 lightPos = { 4.f,4.f,4.f };
	glUniform3f(ent->light,lightPos[0],lightPos[1],lightPos[2]);
	glUniform3f(ent->color_out,ent->color[0],ent->color[1],ent->color[2]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,ent->vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,ent->uvbuffer);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,ent->normalbuffer);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glDrawArrays(GL_TRIANGLES,0,ent->vertices->size);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void destroyEntity(entity* ent)
{
	if(ent->nameid != NULL) free(ent->nameid);
	glDeleteBuffers(1,&ent->vertexbuffer);
	glDeleteBuffers(1,&ent->uvbuffer);
	glDeleteBuffers(1,&ent->normalbuffer);
	glDeleteProgram(ent->program);
	glDeleteVertexArrays(1,&ent->vao);
	Vector_destroy(ent->vertices);
	Vector_destroy(ent->uvs);
	Vector_destroy(ent->normals);
}


