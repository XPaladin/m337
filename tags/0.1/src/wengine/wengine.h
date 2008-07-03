#ifndef WENGINE_H_INCLUDED
#define WENGINE_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>

#include "unit.h"
#include "gamemap.h"

#define TILE_W 30
#define TILE_H 40

typedef std::pair<unit*, SDL_Surface*> unit_pair;
typedef std::vector<unit_pair*> unit_list;
typedef std::vector<SDL_Surface*> surface_list;
typedef std::vector<int> num_list;
typedef std::pair<int, int> coord;

class wengine {
    public:
        const static int game_tic = 10;
        enum direction { UP, RIGHT, DOWN, LEFT };
    protected:
        int width_;
        int height_;
		int paint_from_x_;
		int paint_from_y_;
        SDL_Surface* main_screen_;
        unit_list* units_;
		unit *my_unit;
//        surface_list* terrain_;
        mutable num_list* to_refresh_;
        num_list* occupied_;
		gamemap *terrain_;
    public:
        wengine(int w=20, int h=10);
        virtual ~wengine();

        void init(
                Uint32 init_flags=SDL_INIT_VIDEO,
                Uint32 mode_flags=SDL_HWSURFACE);
        void quit();
        int add_unit(
                const char* unit_name,
                const char* unit_path_to_sprite,
				bool me=false);
        int move_unit(int unit_id, direction dir);
		int init_map(ifstream *archivo);
    protected:
        virtual void main_loop();
        void repaint() const;
        void repaint_terrain() const;
        bool is_occupied(int) const;
        void unoccupy(int);
        int get_tile_index(int, int);
		void calc_from();
};
#endif

