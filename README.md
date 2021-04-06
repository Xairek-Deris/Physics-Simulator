# Physics-Simulator
Small physics simulator that is my first start-to-finish project. 
Will be practicing c++, and specifically object oriented programming,
as well as refreshing some basic physics that I learned in school.

I intentionally avoided calculus in my engine so I could focus on the programming side of things.
I also wanted to test the limits of doing physics with rapid frame updates instead of calculus.

REQUIREMENTS:
SDL runtime binaries and libraries are needed as I do not have the libraries included in the project files yet.

Currently only has hard-coded particles. You can add some more by using pushing back particles into the "particles" vector.
Obstacles are just particles that never move. You create one by pushing a particle into the "obstacles" vector.

The program quickly becomes less accurate if your particles move too fast and/or there are too many particles. This is because 
the physics is done on a separate thread without calculus in the calculations. This means that high update rates are required to
simulate a continuous calculation like calculus would give. Under small ( < 10 ) numbers of particles, with low ( < 20 ) speeds,
the simulation is pretty accurate.

Program only renders 2d because I do not know how to use OpenGL yet. The physics are in 3d, however, so if you set a particle to
Z!=0 then it will work properly, but the view will be silhouettes of the actual motion.

GUI portions are still unimplemented because I am building one by scratch so I can learn how they work.