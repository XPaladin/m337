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
    path << "../data/scenarios/";

    ifstream* cfg_file;
    if (argc==4) {
        path << argv[1];
		s_ip=argv[2];
		port=(Uint16)strtol(argv[3],NULL,0);
    } else {
		printf("%s scenario server port\n",argv[0]);
        path << "2p_Test.cfg";
		s_ip="localhost";
		port=4337;
    }
	m337_engine* eng = new m337_engine(s_ip,port);

    cfg_file = new ifstream(path.str().c_str(), ios_base::in);
    if (!cfg_file->is_open()) {
        cout << "CFG not found" << endl;
        return -1;
    }        

    cout << eng->init_cfg(cfg_file) << endl;
    cfg_file->close();
    
    eng->init();

    eng->quit();

    delete(map_file);
    delete(eng);

    return 0;
}

