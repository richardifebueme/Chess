#pragma once

#include <SDL2/SDL.h>

#include "types.hpp"


class Board {
    public:
        Board();
        int mouse_to_array(int x, int y);
        int square_to_arr(char* str);
        char* arr_to_square(int x);
        char* get_piece_type(int x);

        Cell cells[64];
    private:
};
