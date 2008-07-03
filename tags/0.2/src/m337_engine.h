#include <string>
#include <vector>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "SDL/SDL_thread.h"
#include "tcputil.h"

#include "wengine/wengine.h"

using namespace std;

#define MAXLEN (10*1024) // 10 KB - adequate for text!
class m337_engine: public wengine
{
    protected:
        static const int game_tic = 10;
		IPaddress ip;
		TCPsocket sock;
		Uint16 port;
		string string_ip;
		SDLNet_SocketSet set;
		fd_set fdset;

    public:
        ~m337_engine();
		int done;
		void init();
		m337_engine(string s_ip,Uint16 port);

    protected:
        void main_loop();
};

