
PROGRAM=events
CFLAGS += -Wall -Wextra -g3 -fsanitize=address 
CPP_FLAGS = -Wpedantic -std=c++17 -Wcast-qual -Wnon-virtual-dtor -Woverloaded-virtual -Wold-style-cast
CC=clang++
OBJ_DIR=obj

$(shell mkdir -p obj)

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(CFLAGS) $(CPP_FLAGS)

$(OBJ_DIR)/%.o: %.cpp
	 $(CC) $(CFLAGS) $(CPP_FLAGS) -c $< -o $@

clean:
		rm $(OBJ_DIR)/*
