#include <loadModel.h>



bool loadOBJ(const char* path,Vector* out_vertices,Vector* out_uvs,Vector* out_normals)
{
	Vector *vertexIndices,*uvIndices,*NormalsIndices;
	Vector *temp_vertices,*temp_uvs,*temp_normals;
	vertexIndices = Vector_init(sizeof(uint));
	uvIndices = Vector_init(sizeof(uint));
	NormalsIndices = Vector_init(sizeof(uint));
	temp_vertices = Vector_init(sizeof(vec3));
	temp_uvs = Vector_init(sizeof(vec2));
	temp_normals = Vector_init(sizeof(vec3));

	FILE* file = fopen(path,"r");
	if(file == NULL){
		printf("Problemas en el archivo %s\n",path);
		return false;
	}
	while(1){
		char lineHeader[128];
		int res = fscanf(file,"%s",lineHeader);
		if(res == EOF) break;
		if(strcmp(lineHeader,"v") == 0){
			vec3 vertex;
			fscanf(file,"%f %f %f\n",&vertex[0],&vertex[1],&vertex[2]);
			Vector_pushback(temp_vertices,&vertex);
		}else if(strcmp(lineHeader,"vt") == 0){
			vec2 uv;
			fscanf(file,"%f %f\n",&uv[0],&uv[1]);
			Vector_pushback(temp_uvs,&uv);
		}else if(strcmp(lineHeader,"vn") == 0){
			vec3 normals;
			fscanf(file,"%f %f %f\n",&normals[0],&normals[1],&normals[2]);
			Vector_pushback(temp_normals,&normals);
		}else if(strcmp(lineHeader,"f") == 0){
			uint vertexIndex[3],uvIndex[3],normalIndex[3];
			int matches = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0],&uvIndex[0],&normalIndex[0],
				&vertexIndex[1],&uvIndex[1],&normalIndex[1],
				&vertexIndex[2],&uvIndex[2],&normalIndex[2]);
			if(matches != 9){
				printf("No se puede leer\n");
				return false;
			}
			Vector_pushback(vertexIndices,&vertexIndex[0]);
			Vector_pushback(vertexIndices,&vertexIndex[1]);
			Vector_pushback(vertexIndices,&vertexIndex[2]);
			Vector_pushback(uvIndices,&uvIndex[0]);
			Vector_pushback(uvIndices,&uvIndex[1]);
			Vector_pushback(uvIndices,&uvIndex[2]);
			Vector_pushback(NormalsIndices,&normalIndex[0]);
			Vector_pushback(NormalsIndices,&normalIndex[1]);
			Vector_pushback(NormalsIndices,&normalIndex[2]);
		}else{
			char buffer[1000];
			fgets(buffer,1000,file);
		}
	}
	for(uint i=0; i<vertexIndices->size; i++){
		uint vertexIndex = *(uint*)Vector_getValue(vertexIndices,i);
		uint uvIndex = *(uint*)Vector_getValue(uvIndices,i);
		uint normalIndex = *(uint*)Vector_getValue(NormalsIndices,i);

		vec3 *vertex = (vec3*)Vector_getValue(temp_vertices, vertexIndex-1);
		vec2 *uv = (vec2*)Vector_getValue(temp_uvs,uvIndex-1);
		vec3 *normal = (vec3*)Vector_getValue(temp_normals,normalIndex-1);

		Vector_pushback(out_vertices,vertex);
		Vector_pushback(out_uvs,uv);
		Vector_pushback(out_normals,normal);
	}
		fclose(file);
		return true;
}


