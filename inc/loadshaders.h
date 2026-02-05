#include <stdio.h>
#include <stdlib.h>
#include "glad/glad.h"

typedef unsigned int uint;

int sizeFile(FILE *file);


void GetError(uint shader);

void GetErrorProgram(uint program);
uint LoadShaders(const char *vertex,const char *fragment);