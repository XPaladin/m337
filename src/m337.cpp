#include <iostream>
#include <fstream>
#include <sstream>

#include "m337_engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    m337_engine* eng = new m337_engine;

    stringstream path;
    path << "../data/maps/";

    ifstream* map_file;
    if (argc==2) {
        path << argv[1];
    } else {
        path << "2p_Test";
    }

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

