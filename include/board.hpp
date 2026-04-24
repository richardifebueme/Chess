#pragma once

#include <SDL2/SDL.h>

#include "types.hpp"


class Board {
    private:
    public:
        Board();
        char get_file(int x);
        int get_rank(int x);
        bool is_valid_square(int x);
        bool is_empty_at(int x, int y);
        int mouse_to_array(int x, int y);
        int square_to_arr(char* str);
        char* arr_to_square(int x);
        char* get_piece_type(int x);
        void get_valid_moves(int arr_coord, int* moves_arr);
        void get_squares(int start_square, int rank, int* square_lst, Direction dir);
        // void compute_valid_moves(char** square_lst, char* target_square);

        Cell cells[64];
};
