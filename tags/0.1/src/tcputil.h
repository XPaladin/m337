#ifndef tcputil_h
#define tcputil_h

#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include <cstdlib>
#include <cstring>
char *getMsg(TCPsocket sock, char **buf);
int putMsg(TCPsocket sock, char *buf);
#endif
