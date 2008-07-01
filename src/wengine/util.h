#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <vector>

typedef std::vector<char> char_vector;
typedef std::vector<char_vector> char_matrix;

inline int get_tile_index(int x, int y, int w);

class coordinate
{
    public:
        enum direction { UP, RIGHT, DOWN, LEFT };
        int x;
        int y;
    public:
        coordinate();
        coordinate(int, int);

        coordinate operator+(const coordinate&) const;
        coordinate operator-(const coordinate&) const;
        bool operator<(const coordinate&) const;
        bool operator==(const coordinate&) const;
};

#endif

