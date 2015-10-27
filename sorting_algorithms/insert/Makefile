SRC = insertionsort.cpp
OBJ = $(SRC:.cpp = .o)
PROGRAM = ../insertionsort
CC = g++
CFLAGS = -std=c++11
all:$(PROGRAM)

$(PROGRAM):$(OBJ)
	@$(CC) -o $(PROGRAM) $(OBJ)

SUFFIXES: .cpp

cpp.o:
	@$(CC) $(CFLAGS) -c $<
clean:
	@-rm -rf *.o $(PROGRAM)
