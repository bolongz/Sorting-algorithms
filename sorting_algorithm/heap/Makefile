SRC = heapsort.cpp
OBJ = $(SRC:.cpp = .o)
PROGRAM = ../heapsort
CC = g++
CFLAGS = -std=c++11
all:$(PROGRAM)

$(PROGRAM):$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(PROGRAM)

%.o:%.cpp
	@$(CC) $(CFLAGS)  $< -c $@
clean:
	@-rm -rf *.o $(PROGRAM)
