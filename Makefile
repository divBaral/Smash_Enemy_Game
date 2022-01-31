COMPILER_FLAGS = -Wall -g -std=c++98 
COMPILER_FLAGS += -Iinclude/ -Llib/
CC = g++

#make directories
MKDIR_P = mkdir -p


#header files
DEPS =$(wildcard include/**/*.h)

OBJDIR := build
SRCDIR := src

#directories to be made
OUT_DIR := $(OBJDIR) 
OUT_DIR += userInfo

#source files 
SOURCES = $(wildcard src/*.cpp)

#object files
OBJS_NAME = $(patsubst %.cpp, %.o, $(SOURCES))
OBJS = $(notdir $(OBJS_NAME)) #remove path from the filename
OBJECTS = $(addprefix $(OBJDIR)/, $(OBJS)) #add suitable path in the filename


LINKER_FLAGS =-lBox2D -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

#======================================================================================================

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPS)
	$(CC) $< $(COMPILER_FLAGS) -c -o $@

all : directories $(OBJECTS)
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o game



#build directories
.PHONY : directories

directories: $(OUT_DIR)

$(OUT_DIR):
	$(MKDIR_P) $@



#cleaner
.PHONY : clean

clean : 
	rm -f game
	rm -f build/*.o
#========================================================================================================

