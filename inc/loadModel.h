#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <vector.h>
#include <cglm/cglm.h>
typedef unsigned int uint;

bool loadOBJ(const char* path,Vector* out_vertices,Vector* out_uvs,Vector* out_normals);

