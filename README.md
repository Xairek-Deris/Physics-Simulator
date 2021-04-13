# Physics-Simulator

DESCRIPTION:
My first start-to-finish project. This is a physics simulator that calculates
and renders gravitation, electric attraction, and collision between circular
particles in real time. The project uses SDL2 to render and manage input, 
but the rest of the code was made by me.

PURPOSE:
To gain experience in creating classes, learning how guis work, bugfixing,
and using 3rd party libraries, git, and make.

A side benefit is that I can brush up on some basic physics.

REQUIREMENTS:
SDL2 libraries are required for this project.

Linux is recommended, as I have not yet done testing on windows. The code
should be cross platform, but the makefile might not be.

MAKING:
1. Ensure that the makefile's CFLAGS has the right library path for SDL2.
2. run make config (to produce the intermediates directories)
3. run make

CONTROLS:
e: reverses time in the engine
space: pauses/unpauses the engine

LIMITATIONS:
-Particles are calculated in 3d, but only displayed in 2d for now.
-No commands or GUI implemented yet, so all changed must be hard-coded.

-Because the engine just calculates the force each frame and applies
acceleration, if a particle is moving too fast relative to the
frame rate, it will calculate collisions very wrong. I increased the
frame rate of the engine by running it on a separate thread, so it
would be uncapped by vsync, which greatly improved performance.

-Because the engine indiscriminately calculates particle interactions,
the complexity is O(n^2), greatly affecting the frame rate.

TODO:
Implement GUI.
Use OpenGL to render in 3d.
Optimize particle interactions.