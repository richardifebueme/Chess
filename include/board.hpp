#pragma once

#include <SDL2/SDL.h>

#include "types.hpp"


class Board {
    public:
        Board();
        int get_array_coord(int x, int y);
        char* get_square_notation(int x);

        Cell cells[64];
    private:
};
