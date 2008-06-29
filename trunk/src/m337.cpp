#include <iostream>
#include <fstream>

#include "m337_engine.h"

using namespace std;

int main(int argc, char* argv[]) {
    m337_engine* eng = new m337_engine;
	ifstream *archivo;
	if(argc==2){
		archivo=new ifstream(argv[1]);
		if (!archivo->is_open()){
			cout<<"Map not found"<<endl;
			return -1;
		}

	}
	else{
		cerr<<"Uso %m337 mapa"<<endl;
		return -1;
	}

    cout << eng->init_map(archivo) << endl;
	
	archivo->close();
    
	cout << eng->add_unit("Char01", "../images/players/male01.png") << endl;
    cout << eng->add_unit("Char02", "../images/players/female01.png") << endl;

    eng->init();

    eng->quit();

    delete(eng);

    return 0;
}

