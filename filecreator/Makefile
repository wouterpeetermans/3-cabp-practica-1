#OBJS specifies wicht files to compile
OBJS = src/main.cpp 

#CC spesifies compiler
CC = g++
#CW is compiler for windows
CW = i586-mingw32msvc-g++
#COMPILER_FLAGS aditional options to use
#-w suppress all warnings
COMPILER_FLAGS = -Wall -std=c++11

#LINKER_FLAGS linked libraries
LINKER_FLAGS = 
LINKER_FLAGS_WIN = 

#OBJ_NAME name of the compiled file
OBJ_NAME = out/practica-1

#compile to executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


