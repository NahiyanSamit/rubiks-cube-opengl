# Rubik's Cube (OpenGL + GLUT)

A simple Rubik's Cube viewer with basic layer rotations using OpenGL and GLUT (FreeGLUT).

## Project Structure

- `include/app.h` — App/GLUT callbacks (init, display, reshape, input)
- `include/cube.h` — Cube data structures and move queue API
- `include/math.h` — Minimal 4x4 matrix helpers for transforms
- `src/app.cpp` — Rendering, input handling, animation/update loop
- `src/cube.cpp` — Cubelet transforms, move queue, layer rotation logic
- `src/main.cpp` — Program entry and GLUT setup
- `Makefile` — Build script

## Build

Requirements (Linux):
- OpenGL, GLU, and FreeGLUT development packages
  - Debian/Ubuntu: `sudo apt install build-essential freeglut3-dev libglu1-mesa-dev mesa-common-dev`

Build commands:

```
make            # or: make main
```

This produces the executable:

```
./rubiks_cube
```

Clean:

```
make clean
```

## Run

```
./rubiks_cube
```

## Controls

- Mouse
  - Right click + drag: rotate the whole cube (orbit-like)
  - Left click + drag: rotate a single layer
    - Horizontal drag: rotates a layer around the Y axis
    - Vertical drag: rotates a layer around the X axis
    - The layer is chosen by the vertical position of the mouse when you click (top/middle/bottom)

- Keyboard
  - W/S: tilt cube up/down
  - A/D: spin cube left/right
  - E: toggle animation for queued moves
  - Layer hotkeys (lowercase = clockwise, uppercase = counter‑clockwise):
    - X‑axis layers: `z` (bottom), `x` (middle), `c` (top)
    - Y‑axis layers: `n` (left), `b` (middle), `v` (right)

## Notes

- Back‑face culling is disabled to avoid gaps between cubelets. If you enable it, ensure face winding remains consistent after transforms.
- If borders flicker against faces, consider using polygon offset for the filled quads or reducing line width.