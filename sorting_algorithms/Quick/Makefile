SRC = quicksort.cpp
OBJ = $(SRC:.cpp = .o)
PROGRAM = ../../quicksort
CC = g++
CFLAGS = -std=c++11 -g
all:$(PROGRAM)

$(PROGRAM):$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(PROGRAM)

%.o:%.cpp
	@$(CC) $(CFLAGS)  $< -c $@
clean:
	@-rm -rf *.o $(PROGRAM)
