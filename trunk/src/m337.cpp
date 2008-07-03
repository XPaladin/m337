#include <iostream>
#include <fstream>
#include <sstream>

#include "m337_engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    stringstream path;
	const char *s_ip;
	Uint16 port;
    path << "../data/maps/";

    ifstream* map_file;
    if (argc==4) {
        path << argv[1];
		s_ip=argv[2];
		port=(Uint16)strtol(argv[3],NULL,0);
    } else {
		printf("%s map server port\n",argv[0]);
        path << "2p_Test";
		s_ip="localhost";
		port=4337;
    }
	m337_engine* eng = new m337_engine(s_ip,port);

    map_file = new ifstream(path.str().c_str(), ios_base::in);
    if (!map_file->is_open()) {
        cout << "Map not found" << endl;
        return -1;
    }        

    cout << eng->init_map(map_file) << endl;
    map_file->close();
    
    cout << eng->add_unit("Char01", "../images/players/male01.png") << endl;
    cout << eng->add_unit("Char02", "../images/players/female01.png") << endl;

    eng->init();

    eng->quit();

    delete(map_file);
    delete(eng);

    return 0;
}

