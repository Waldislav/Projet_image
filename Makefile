CCC=g++
UNAME := $(shell uname)
CFLAGS=-Wall -I/urs/local/include
CFLAGS=
ifeq ($(UNAME), Darwin)
	#LDFLAGS=-framework OpenGL -framework GLUT -lGLEW -lm  -llapack -lblas
	LDFLAGS= -framework OpenGL -framework GLUT -lm
else
	#LDFLAGS= -lGL -lGLEW -lGLU -lglut  -lm  -llapack -lblas
	LDFLAGS= -lGL -lGLU -lglut  -lm
endif

SRC=cube.cpp chariot.cpp courbe.cpp rail.cpp main.cpp
DEBUBFLAG=-g

OBJ= $(SRC:.cpp=.o)
BIN=./
EXEC=main

all: $(EXEC)

main: $(OBJ)
		$(CCC) -g -o $(BIN)$@ $^ $(LDFLAGS)

%.o: %.cpp point.h
		$(CCC) -g -o $@ -c $< $(CFLAGS)


clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(BIN)$(EXEC)

