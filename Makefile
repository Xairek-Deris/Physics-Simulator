CC = g++
CFLAGS = -std=gnu++17 -L /usr/local/lib

SRC = src
DISP_SRC = $(SRC)/display
EVEN_SRC = $(SRC)/events
PHYS_SRC = $(SRC)/physics

BLD = build
DISP_BLD = $(BLD)/display
EVEN_BLD = $(BLD)/events
PHYS_BLD = $(BLD)/physics


_PHYS_H = camera.h clock.h particle.h vector.h
_DISP_H = box.h point.h renderer.h texture.h thread.h window.h
_EVEN_H = dispatcher.h event.h handler.h queue.h

_PHYS_O = clock.o particle.o vector.o
_DISP_O = display.o renderer.o texture.o window.o
_EVEN_O = queue.o

DISP_H = $(patsubst %, $(DISP_SRC)/%, $(_DISP_H))
EVEN_H = $(patsubst %, $(EVEN_SRC)/%, $(_EVEN_H))
PHYS_H = $(patsubst %, $(PHYS_SRC)/%, $(_PHYS_H))

DISP_O = $(patsubst %, $(DISP_BLD)/%, $(_DISP_O))
EVEN_O = $(patsubst %, $(EVEN_BLD)/%, $(_EVEN_O))
PHYS_O = $(patsubst %, $(PHYS_BLD)/%, $(_PHYS_O))


bin/simulation: $(BLD)/main.o $(BLD)/engine.o $(DISP_O) $(PHYS_O)
	$(CC) $(CFLAGS) $(BLD)/main.o $(BLD)/engine.o $(DISP_O) $(PHYS_O) -lSDL2 -o $@

$(BLD)/main.o: 	$(SRC)/main.cpp $(SRC)/engine.h\
				$(DISP_SRC)/display.h $(PHYS_SRC)/physics.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/engine.o: 	$(SRC)/engine.cpp $(SRC)/engine.h\
					$(DISP_SRC)/display.h $(PHYS_SRC)/physics.h
	$(CC) $(CFLAGS) -c $< -o $@


$(DISP_BLD)/%.o: $(DISP_SRC)/%.cpp $(DISP_SRC)/display.h
	$(CC) $(CFLAGS) -c $< -o $@

$(EVEN_BLD)/%.o: $(EVEN_SRC)/%.cpp $(EVEN_SRC)/events.h
	$(CC) $(CFLAGS) -c $< -o $@

$(PHYS_BLD)/%.o: $(PHYS_SRC)/%.cpp $(PHYS_SRC)/physics.h
	$(CC) $(CFLAGS) -c $< -o $@


$(DISP_SRC)/display.h: $(DISP_H)
	touch $(DISP_SRC)/display.h

$(EVEN_SRC)/events.h: $(EVEN_H)
	touch $(EVEN_SRC)/events.h

$(PHYS_SRC)/physics.h: $(PHYS_H)
	touch $(PHYS_SRC)/physics.h


config:
	mkdir bin build build/physics build/display build/events

clean:
	rm build/*.o build/display/*.o build/events/*.o build/physics/*.o