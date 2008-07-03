CPPC=g++
CFLAGS=-Wall -pedantic -g
SDLFLAGS=`sdl-config --cflags`
LIBS=`sdl-config --libs` -lSDL_image -lSDL_net
BIN_DIR=../bin/
EXE=$(BIN_DIR)m337
SERV=$(BIN_DIR)server

all: m337 server

server: m337_server.cpp tcputil.o
	$(CPPC) $(LIBS) -o $(BIN_DIR)$@ $^

m337: m337.cpp m337_engine.o wengine.o unit.o gamemap.o tcputil.o
	$(CPPC) $(LIBS) -o $(BIN_DIR)$@ $^

tcputil.o: tcputil.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

m337_engine.o: m337_engine.cpp wengine.o
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

parser.o: wengine/parser.cpp config.o
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

config.o: wengine/config.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

wengine.o: wengine/wengine.cpp unit.o gamemap.o parser.o config.o
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

unit.o: wengine/unit.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

gamemap.o: wengine/gamemap.cpp
	$(CPPC) $(CFLAGS) $(SDLFLAGS) -c $<

clean:
	rm -rf *.o wengine/*.o $(EXE) $(SERV)
