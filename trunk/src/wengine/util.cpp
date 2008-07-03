#include "util.h"

namespace util {
    inline int get_tile_index(int x, int y, int w)
    {
        return x + y*w;
    }
}

