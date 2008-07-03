#include "wengine.h"

wengine::wengine(int w, int h) :
    width_ (w),
    height_ (h),
    units_ (new unit_list),
    to_refresh_ (new num_list),
    occupied_ (new num_list)
{
    

}

wengine::~wengine()
{
    delete(occupied_);
    delete(to_refresh_);
    delete(terrain_);
    for (unsigned int i=0; i<units_->size(); ++i) {
        delete(units_->at(i)->first);
        SDL_FreeSurface(units_->at(i)->second);
        delete(units_->at(i));
    }
    delete(units_);

}

void wengine::init(Uint32 init_flags, Uint32 mode_flags)
{
	paint_from_x_=0;
	paint_from_y_=0;

    SDL_Init(init_flags);
    main_screen_ = SDL_SetVideoMode(width_*TILE_W, height_*TILE_H,
            0, mode_flags);
    SDL_WM_SetCaption("m337", NULL);
    main_loop();
}

void wengine::quit()
{
    SDL_Quit();
}

void wengine::main_loop()
{
}

int wengine::add_unit(const char* name, const char* path_to_sprite, bool me)
{
    unit* new_unit = new unit(name, path_to_sprite);
    SDL_Surface* img = IMG_Load(new_unit->get_path_to_sprite().c_str());
    if (img == NULL) {
        delete(new_unit);
        return -1;
    } else {
        int id = new_unit->get_id();
        units_->push_back(new unit_pair(new_unit, img));
        new_unit->x = id==0?1:10;//id % terrain_->w_+1;
        new_unit->y = id==0?1:10;//(id / terrain_->w_) * height_+2;
        occupied_->push_back(get_tile_index(new_unit->x,new_unit->y));
		if(me){
			my_unit=new_unit;
			calc_from();
		}
        return id;
    }
}

void wengine::repaint() const
{
    SDL_Rect rect;
    unit* u;

    /* terrain */
    repaint_terrain();

    /* units */
    for (unit_list::iterator i = units_->begin(); i != units_->end(); ++i) {
        u = (*i)->first;
        if (u->x < 0 || u->y < 0) { continue; }
        rect.x = TILE_W*(u->x-paint_from_x_);
        rect.y = TILE_H*(u->y-paint_from_y_);
		if(rect.y>=0 &&rect.x>=0){
      	  SDL_BlitSurface((*i)->second, NULL, main_screen_, &rect);
		}
    }

    /* update screen */
    SDL_UpdateRect(main_screen_, 0, 0, 0, 0);
}

int wengine::move_unit(int unit_id, direction dir)
{
    unit* u = NULL;

    for (unit_list::iterator i = units_->begin(); i != units_->end(); ++i) {
        if ((u = (*i)->first)->get_id() == unit_id) {
            break;
        }
    }

    if (u == NULL) {
        return -1;
    } else {
        int src_tile_index;
        int dst_tile_index;

        src_tile_index = get_tile_index(u->x, u->y);
		
        switch (dir) {
            case UP:
                dst_tile_index = get_tile_index(u->x, u->y-1);
                if (is_occupied(dst_tile_index)) {
                    return -1;
                }
                u->y--;
                break;
            case RIGHT:
                dst_tile_index = get_tile_index(u->x+1, u->y);
                if (is_occupied(dst_tile_index)) {
                    return -1;
                }
                u->x++;
                break;
            case DOWN:
                dst_tile_index = get_tile_index(u->x, u->y+1);
                if (is_occupied(dst_tile_index)) {
                    return -1;
                }
                u->y++;
                break;
            case LEFT:
                dst_tile_index = get_tile_index(u->x-1, u->y);
                if (is_occupied(dst_tile_index)) {
                    return -1;
                }
                u->x--;
                break;
        }
        unoccupy(src_tile_index);
/*		if(u==my_unit){//no yo
	        to_refresh_->push_back(src_tile_index);
		}else{//yo me movi
			for(int i=0;i<terrain_->w_*terrain_->h_;i++){
				to_refresh_->push_back(i);
			}
		}
*/
        occupied_->push_back(dst_tile_index);
		calc_from();
        return 0;
    }
}

void wengine::repaint_terrain() const
{
    SDL_Rect rect;
    int n;
	SDL_Surface* img;
    for (/*unsigned*/ int i=0; i</*to_refresh_->size()*/terrain_->w_*terrain_->h_; ++i) {
//        n = to_refresh_->at(i);
		n=i;
        rect.x=  ((n%terrain_->w_)-paint_from_x_) * TILE_W;
        rect.y=  ((n/terrain_->w_)-paint_from_y_) * TILE_H;
		img = IMG_Load(terrain_->get_path_to_sprite(n).c_str());
		if(rect.y>=0 &&rect.x>=0){
        	SDL_BlitSurface(img, NULL, main_screen_, &rect);
		}
		SDL_FreeSurface(img);
    }
//    to_refresh_->clear();

}

bool wengine::is_occupied(int tile_index) const
{
    for (num_list::iterator i = occupied_->begin(); i != occupied_->end();
            ++i) {
        if (*i == tile_index) {
            return true;
        }
    }
    return false;
}

void wengine::unoccupy(int tile_index)
{
    for (num_list::iterator i = occupied_->begin(); i != occupied_->end();
            ++i) {
        if (*i == tile_index) {
            occupied_->erase(i);
            return;
        }
    }
}

int wengine::get_tile_index(int x, int y)
{
    return x + y*terrain_->w_;
}

int wengine::init_map(ifstream *map_file)
{
	int w,h;
	string linea;
    getline(*map_file,linea);
	sscanf(linea.c_str(),"%d %d",&w,&h);
	printf("%d,%d\n",w,h);
    terrain_=new gamemap(w,h, map_file);
    for(int n=0;n<w*h;n++){
//        to_refresh_->push_back(n);
        if (terrain_->es_muro(n)) {
            occupied_->push_back(n);
        }
    }
    return 0;
}
//calcula un area tal que mi unidad quede en el medio
void wengine::calc_from()
{
	if(my_unit==NULL){//sin unidad no hay mucho que hacer
		paint_from_x_=0;
		paint_from_y_=0;
		return;
	}
	paint_from_x_=max(my_unit->x-width_/2,0);
	paint_from_x_=min(paint_from_x_,width_);
	paint_from_y_=max(my_unit->y-height_/2,0);		
	paint_from_y_=min(paint_from_y_,height_);


}
