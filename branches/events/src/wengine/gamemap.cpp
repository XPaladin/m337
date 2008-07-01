#include "gamemap.h"

int gamemap::get_tile_path_to_sprite(char symbol, string& path)
{
    path.clear();

    path.append("../images/terrain/");
    switch (symbol) {
        case ' ':
            path.append("dirt.png");
            break;
        case 'w':
            path.append("wall_1.png");
            break;
        default:
            return -1;
    }

    return 0;
}

string gamemap::get_path_to_sprite(int n) {
    string path;
    if (n<0 || n>=w_*h_) {
        return "../images/terrain/dirt.png";
    }

    if (get_tile_path_to_sprite(charmap_[n],path)==0) {
        return path;
    } else {
        return "Error";
    }
}

gamemap::gamemap(int w, int h, ifstream *archivo):
    h_(h),
    w_(w)
{	
    charmap_=new char[h_*w_];
    string linea;
    string path;
    for (int i=0; i<h_; ++i) {
        getline(*archivo,linea);
        for(int j=0;j<w_; ++j){
            charmap_[i*w_+j]=linea[j];
            
        }	    
    }
}

gamemap::~gamemap()
{
    delete [] charmap_;
}

bool gamemap::es_muro(int n)
{
    return charmap_[n]=='w';
}

