CPPC=g++
CFLAGS=-Wall -pedantic -g
SDLFLAGS=`sdl-config --cflags`
LIBS=`sdl-config --libs` -lSDL_image
BIN_DIR=../bin/
EXE=$(BIN_DIR)m337

all: m337

m337: m337.cpp m337_engine.o wengine.o unit.o gamemap.o
	$(CPPC) $(LIBS) -o $(BIN_DIR)$@ $^

m337_engine.o: m337_engine.cpp wengine.o
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

wengine.o: wengine/wengine.cpp unit.o gamemap.o
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

unit.o: wengine/unit.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

gamemap.o: wengine/gamemap.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

util.o: wengine/util.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

config.o: wengine/config.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

parser.o: wengine/parser.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

clean:
	rm -rf *.o wengine/*.o $(EXE)
