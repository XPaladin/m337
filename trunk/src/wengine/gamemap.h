#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include <string>

#include "util.h"
#include <iostream>
#include <fstream>

using namespace std;

class gamemap
{
    public:
        gamemap();
        gamemap(int h,int w,ifstream *archivo);
        ~gamemap();
        string get_path_to_sprite(int n);		
        bool es_muro(int n);

    protected:
        int get_tile_path_to_sprite(char symbol, string& path);
        int h_, w_;
        char *charmap_;
};

#endif

