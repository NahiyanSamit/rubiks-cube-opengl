CC = g++
CFLAGS = -I./include
LDFLAGS = -lGL -lGLU -lglut

SRC = src/main.cpp src/cube.cpp src/app.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = rubiks_cube

all: $(EXEC)

# Alias so `make main` works
.PHONY: main
main: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile files under src/ into src/*.o
src/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean