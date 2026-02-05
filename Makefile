#CFLAGS		:= -std=c23 -Wall -pedantic -Wall -Wpedantic -Werror -Wextra
include		:= -Iinc -Ilibs
source		:= src
SRC		:= $(shell find $(source) -type f -name '*.c')
objects		:= obj
OBJS		:= $(patsubst $(source)/%.c,$(objects)/%.o,$(SRC))
LIBS		:= -Llibs -lcglm -lSDL3 -lc -lm
PROJECT		:= libframework-phisics.so


.PHONY:

all: config $(PROJECT)

$(PROJECT): $(objects) $(OBJS)
	gcc -shared obj/glad.o $(OBJS) $(LIBS) -o $(PROJECT)

$(objects)/%.o: $(source)/%.c
	gcc -std=c23 $(CFLAGS) $< -c -o $@ $(include) -g -O3 -fPIC

config:
	mkdir -p obj bin bin/shaders
	cp shaders/* bin/shaders/
	gcc -std=c23 libs/glad/glad.c -c -o obj/glad.o -Ilibs -fPIC

clean:
	rm -fr obj

1:
	gcc main.c src/loadshaders.c obj/glad.o -o game -lSDL3 -Ilibs -Iinc

