#include "m337_engine.h"

m337_engine::~m337_engine()
{
}
m337_engine::m337_engine(string s_ip,Uint16 p) :
    string_ip(s_ip),port(p)
{
//	wengine::wengine();
	done=0;


}
void m337_engine::init(){
	// initialize SDL
	if(SDL_Init(0)==-1)
	{
		printf("SDL_Init: %s\n",SDL_GetError());
		exit(1);
	}

	// initialize SDL_net
	if(SDLNet_Init()==-1)
	{
		printf("SDLNet_Init: %s\n",SDLNet_GetError());
		SDL_Quit();
		exit(3);
	}
	set=SDLNet_AllocSocketSet(1);
	if(!set)
	{
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(4); //most of the time this is a major error, but do what you want.
	}
	
	// Resolve the argument into an IPaddress type
	printf("Connecting to %s port %d\n",string_ip.c_str(),port);
	if(SDLNet_ResolveHost(&ip,string_ip.c_str(),port)==-1)
	{
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(5);
	}

	// open the server socket
	sock=SDLNet_TCP_Open(&ip);
	if(!sock)
	{
		printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(6);
	}
	
	if(SDLNet_TCP_AddSocket(set,sock)==-1)
	{
		printf("SDLNet_TCP_AddSocket: %s\n",SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(7);
	}


	wengine::init();
}

typedef struct{
	TCPsocket sock;
	m337_engine *engine;
}DATA;

int net_thread_main(void *data);

void m337_engine::main_loop()
{

	char message[MAXLEN];
    bool close = false;
    SDL_Event event;
	SDL_Thread *net_thread=NULL;
	
	DATA *datos;
    datos = new DATA;
	datos->sock=sock;
	datos->engine=this;
	net_thread=SDL_CreateThread(net_thread_main,datos);
	if(!net_thread)
	{
		printf("SDL_CreateThread: %s\n",SDL_GetError());
		SDLNet_Quit();
		SDL_Quit();
		exit(9);
	}
    while (!close) {
        repaint();
        while (SDL_PollEvent(&event)) {
			
            switch (event.type) {
                case SDL_QUIT:
                    close = true;
					done=1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            close = true;
							done=1;
							break;
		            	case SDLK_UP:
		    	            message[0]='0';
				            break;
						case SDLK_RIGHT:
		    	            message[0]='1';
			                break;
			            case SDLK_DOWN:
		    	            message[0]='2';
			                break;
		            	case SDLK_LEFT:
		    	            message[0]='3';
		        	        break;
						default:
							break;
                    }
				message[1]='\0';
				putMsg(sock,message);
            }
			
        }
		SDL_Delay(game_tic);
	}
	done=1;
	delete datos;
//	SDL_KillThread(net_thread);
	SDL_WaitThread(net_thread,NULL);

	// this shows our unique reason where the threads ended
	printf("Finished code %d\n",done);
	
}
int net_thread_main(void *data)
{
	TCPsocket sock=((DATA *)data)->sock;
	m337_engine *thees=((DATA *)data)->engine;
	SDLNet_SocketSet set;
	char *str=NULL;
	char accion;
	int pl,numready;

	set=SDLNet_AllocSocketSet(1);
	if(!(thees->done) && !set)
	{
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		thees->done=2;
	}

	if(!(thees->done) && SDLNet_TCP_AddSocket(set,sock)==-1)
	{
		printf("SDLNet_TCP_AddSocket: %s\n",SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		thees->done=3;
	}
	
	while(!(thees->done))
	{
		numready=SDLNet_CheckSockets(set, (Uint32)-1);
		if(numready==-1)
		{
			printf("SDLNet_CheckSockets: %s\n",SDLNet_GetError());
			thees->done=4;
			break;
		}

		// check to see if the server sent us data
		if(numready && SDLNet_SocketReady(sock))
		{
			// getMsg is in tcputil.h, it gets a string from the socket
			// with a bunch of error handling
			if(!getMsg(sock,&str))
			{
				char *errstr=SDLNet_GetError();
				printf("getMsg: %s\n",strlen(errstr)?errstr:"Server disconnected");
				thees->done=5;
				break;
			}
			// act according
			sscanf(str,"%d %c",&pl,&accion);
			switch(accion){
	           	case '0':
	           		thees->move_unit(pl, thees->UP);
			           break;
				case '1':
	                thees->move_unit(pl, thees->RIGHT);
	           	    break;
		        case '2':
		            thees->move_unit(pl, thees->DOWN);
		            break;
		        case '3':
		            thees->move_unit(pl, thees->LEFT);
		            break;
				default:
		           	break;
			}
	    	printf("%s\n",str);
		}//if numready && SocketReady
	}
	if(!(thees->done)){
		thees->done=1;
	}
	return(0);
}


