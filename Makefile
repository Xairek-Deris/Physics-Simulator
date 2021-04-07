MYFLAGS = g++ -std=gnu++17
SDL_LIB = /usr/local/lib/libSDL2.so

application.out: intermediates/main.o intermediates/particle.o intermediates/engine.o intermediates/window.o
	$(MYFLAGS) intermediates/main.o intermediates/particle.o intermediates/window.o $(SDL_LIB) intermediates/engine.o -o $@

main.o: src/main.cpp src/Physics/vector.h src/Physics/particle.h src/Physics/camera.h \
		src/Physics/clock.h src/Display/window.h src/Display/thread.h \
		src/Display/renderer.h src/Display/texture.h src/Display/point.h src/Display/box.h src/engine.h
	$(MYFLAGS) -c src/main.cpp -o intermediates/$@

particle.o: src/Physics/particle.cpp src/Physics/particle.h src/Physics/vector.h
	$(MYFLAGS) -c src/Physics/particle.cpp -o intermediates/$@

engine.o: src/engine.cpp src/engine.h src/Display/thread.h src/Physics/camera.h src/Physics/clock.h
	$(MYFLAGS) -c src/engine.cpp -o intermediates/$@

window.o: src/Display/window.cpp src/Display/window.h
	$(MYFLAGS) -c src/Display/window.cpp -o intermediates/$@