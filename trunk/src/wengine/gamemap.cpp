#include "gamemap.h"

int gamemap::get_tile_path_to_sprite(char symbol, string& path)
{
    switch (symbol) {
        case ' ':
            path.clear();
            path.assign("../images/terrain/dirt.png");
		    break;
        case 'w':
            path.clear();
            path.assign("../images/terrain/wall 1.png");
	    	break;
        default:
            return -1;
    }

    return 0;
}
string gamemap::get_path_to_sprite(int n){
	string path;
	if(n<0||n>=w_*h_)return "../images/terrain/dirt.png";
	if(get_tile_path_to_sprite(charmap_[n],path)==0)
		return path;
	else return "Error";
}
gamemap::gamemap(int w, int h, ifstream *archivo):
h_(h),w_(w)
{	
	charmap_=new char[h_*w_];
//	units_=new
//	cout<<h<<w<<endl;
	string linea;
	string path;
	for (int i=0; i<h_; ++i) {
		getline(*archivo,linea);
		for(int j=0;j<w_; ++j){
			charmap_[i*w_+j]=linea[j];
			
		}	    
    }
/*	for (int i=0; i<h_; ++i) {
		for(int j=0;j<w_; ++j){
			cout<<charmap_[i*w_+j];
		}
		cout<<endl;
	}
*/
}
gamemap::~gamemap()
{
//	for (int i=0; i<h_; ++i) {
//		delete [] charmap_[i];
//	}
	delete [] charmap_;
}
bool gamemap::es_muro(int n)
{
	return charmap_[n]=='w';
}
