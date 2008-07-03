#include "wengine.h"

wengine::wengine(int w, int h) :
    width_ (w),
    height_ (h),
    units_ (new unit_list),
    to_refresh_ (new num_list),
    occupied_ (new num_list)
{
    for (int i=0; i<w*h; ++i) {
        to_refresh_->push_back(i);
    }

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
    SDL_Init(init_flags);
    main_screen_ = SDL_SetVideoMode(width_*TILE_W, height_*TILE_H,
            0, mode_flags);
    SDL_WM_SetCaption("m337", NULL);


	child_list *cl = configuration_->get_children("scenario");
	config* c = cl->first();

	ifstream* map_file;
	map_file = new ifstream((*c)["map_data"], ios_base::in);
	
    if (!map_file->is_open()) {
        cout << "map not found" << endl;
    	return;
    }     
	cout << init_map(map_file) << endl;

	if(atoi( (*c)["player_number"].c_str() )==2){
	    cout << add_unit("Char01", "../images/players/male01.png") << endl;
    	cout << add_unit("Char02", "../images/players/female01.png") << endl;
	}
	
    main_loop();
}

void wengine::quit()
{
    SDL_Quit();
}

void wengine::main_loop()
{
}

int wengine::add_unit(const char* name, const char* path_to_sprite)
{
    unit* new_unit = new unit(name, path_to_sprite);
    SDL_Surface* img = IMG_Load(new_unit->get_path_to_sprite().c_str());

    if (img == NULL) {
        delete(new_unit);
        return -1;
    } else {
        int id = new_unit->get_id();
        units_->push_back(new unit_pair(new_unit, img));
        new_unit->x = id % width_;
        new_unit->y = (id / width_) * height_+1;
        occupied_->push_back(get_tile_index(new_unit->x,new_unit->y));
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
        rect.x = TILE_W*u->x;
        rect.y = TILE_H*u->y;
        SDL_BlitSurface((*i)->second, NULL, main_screen_, &rect);
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
        to_refresh_->push_back(src_tile_index);
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
        occupied_->push_back(dst_tile_index);
        return 0;
    }
}

void wengine::repaint_terrain() const
{
    SDL_Rect rect;
    int n;
	SDL_Surface* img;
    for (unsigned int i=0; i<to_refresh_->size(); ++i) {
        n = to_refresh_->at(i);
        rect.x=  (n%width_) * TILE_W;
        rect.y=  (n/width_) * TILE_H;
		img = IMG_Load(terrain_->get_path_to_sprite(n).c_str());
        SDL_BlitSurface(img, NULL, main_screen_, &rect);
		SDL_FreeSurface(img);
    }
    to_refresh_->clear();

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
    return x + y*width_;
}

int wengine::init_map(ifstream *map_file)
{
    terrain_=new gamemap(width_,height_, map_file);
    for(int n=0;n<width_*height_;n++){
        if (terrain_->es_muro(n)) {
            occupied_->push_back(n);
        }
    }
    return 0;
}

int wengine::init_cfg(ifstream *cfg_file)
{
	parser par;
	par.parse(*cfg_file, *configuration_);
	return 1;

}
