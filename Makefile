CC = g++
CFLAGS = -I./src
LDFLAGS = -lGL -lGLU -lglut
SRC = src/main.cpp src/cube.cpp src/input.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = rubiks_cube

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)