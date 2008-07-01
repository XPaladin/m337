#include "util.h"

inline int get_tile_index(int x, int y, int w)
{
    return x + y*w;
}

coordinate::coordinate() :
    x (0),
    y (0)
{
}

coordinate::coordinate(int x, int y) :
    x (x),
    y (y)
{
}

coordinate coordinate::operator+(const coordinate& coord) const
{
    return coordinate (x + coord.x, y + coord.y);
}

coordinate coordinate::operator-(const coordinate& coord) const
{
    coordinate c(x - coord.x, y - coord.y);
    return c;
}

bool coordinate::operator<(const coordinate& coord) const
{
    return x < coord.x;
}

bool coordinate::operator==(const coordinate& coord) const
{
    return x == coord.x && y == coord.y;
}

