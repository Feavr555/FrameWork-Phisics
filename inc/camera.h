#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <cglm/cglm.h>
#include <SDL3/SDL.h>
typedef unsigned int uint;

void computeMatricesFromInputs();
void getViewMatrix(mat4 outViewMatrix);
void getProjectionMatrix(mat4 outProjectionMatrix);

