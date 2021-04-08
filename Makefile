#please excuse the mess, I have never used one of these before.

MYFLAGS = g++ -std=gnu++17
SDL_LIB = /usr/local/lib/libSDL2.so
PHYS = src/Physics
DISP = src/Display
EVENT = src/Event

application.out: intermediates/main.o intermediates/particle.o intermediates/engine.o intermediates/window.o
	$(MYFLAGS) $(SDL_LIB) intermediates/main.o intermediates/particle.o intermediates/window.o intermediates/engine.o -o $@

intermediates/main.o: src/main.cpp $(PHYS)/vector.h $(PHYS)/particle.h $(PHYS)/camera.h \
					  $(PHYS)/clock.h $(DISP)/window.h $(DISP)/thread.h $(DISP)/renderer.h \
					  $(DISP)/texture.h $(DISP)/point.h $(DISP)/box.h $(EVENT)/event.h \
					  $(EVENT)/queue.h $(EVENT)/handler.h src/engine.h
	$(MYFLAGS) -c src/main.cpp -o $@

intermediates/particle.o: $(PHYS)/particle.cpp $(PHYS)/particle.h $(PHYS)/vector.h
	$(MYFLAGS) -c $(PHYS)/particle.cpp -o $@

intermediates/engine.o: src/engine.cpp src/engine.h $(DISP)/thread.h $(PHYS)/camera.h $(PHYS)/clock.h
	$(MYFLAGS) -c src/engine.cpp -o $@

intermediates/window.o: $(DISP)/window.cpp $(DISP)/window.h
	$(MYFLAGS) -c $(DISP)/window.cpp -o $@