# Rubik's Cube Project

This project is a graphical representation of a Rubik's Cube using OpenGL and GLUT. It allows users to visualize the cube and interact with it through mouse input.

## Project Structure

The project is organized into the following files:

- `src/main.cpp`: The entry point of the application. Initializes GLUT, sets up the window, and registers display and input handling functions.
- `src/cube.cpp`: Contains the implementation of the cube drawing logic, including the `drawCube` function.
- `src/cube.h`: Declares the `drawCube` function and necessary structures related to cube drawing.
- `src/input.cpp`: Implements mouse input handling functions, including `mouseClick`, `mouseMotion`, and `passiveMotion`.
- `src/input.h`: Declares the mouse input handling functions for use in the main application.
- `Makefile`: Contains build instructions for compiling the project.

## Building the Project

To build the project, navigate to the project directory and run the following command:

```
make
```

This will compile the source files and create an executable.

## Running the Application

After building the project, you can run the application with the following command:

```
./rubiks-cube
```

## Controls

- **Right-click and drag**: Rotate the entire Rubik's cube in 3D space
  - Horizontal mouse movement rotates around the Y-axis
  - Vertical mouse movement rotates around the X-axis
- **Left-click and drag**: Rotate individual layers/rows of the cube
  - Horizontal drag rotates layers around the Y-axis (top/bottom layers)
  - Vertical drag rotates layers around the X-axis (left/right layers)
- Mouse movement coordinates are displayed in the console for debugging

## Dependencies

This project requires the following libraries:

- OpenGL
- GLUT

Make sure these libraries are installed on your system before building the project.