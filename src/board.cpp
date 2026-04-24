#include <cstdlib>
#include <deque>
#include <iostream>
#include <string.h>

#include "board.hpp"
#include "constants.hpp"
#include "types.hpp"

using namespace std;

Board::Board() {
    std::deque<PieceType> init_pos = {
        B_ROOK, B_KNIGHT, B_BISHOP, B_KING, B_QUEEN, B_BISHOP, B_KNIGHT, B_ROOK,
        B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN,
        W_ROOK, W_KNIGHT, W_BISHOP, W_KING, W_QUEEN, W_BISHOP, W_KNIGHT, W_ROOK,
    };

    for (auto& cell : cells) {
        cell.piece.type = init_pos.front();
        init_pos.pop_front();
    }

    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            cells[i + (j*ROW_SIZE)].rect = {i * CELL_WIDTH + BOARD_X, j * CELL_HEIGHT + BOARD_Y, CELL_WIDTH, CELL_HEIGHT};
        }
    }

    for (int i = 0; i < 64; i++) {
        strcpy(cells[i].piece.square_notation, arr_to_square(i));
    }
}

char Board::get_file(int x) {
    if (!is_valid_square(x)) {
        cout << "the value must not be greater than 63" << endl;
        return -1;
    }

    char file = (x % ROW_SIZE) + 97;
    return file;
}

int Board::get_rank(int x) {
    if (!is_valid_square(x)) {
        cout << "the value must not be greater than 63" << endl;
        return -1;
    }

    int rank = ROW_SIZE - (x / ROW_SIZE);

    return rank;
}

bool Board::is_valid_square(int x) {
    if (x >= 0 && x < 64) {
        return true;
    }

    return false;
}

bool Board::is_empty_at(int x, int y) {
    int arr_coord = mouse_to_array(x, y);
    if (cells[arr_coord].piece.type == EMPTY) return true;

    return false;
}

int Board::mouse_to_array(int x, int y) {
    if (x < BOARD_X || x > BOARD_X + BOARD_WIDTH || y < BOARD_Y || y > BOARD_Y + BOARD_HEIGHT) return -1;
    int row = (x / CELL_WIDTH) - 1;
    int col = (y / CELL_HEIGHT) - 1;
    return (row + (col*ROW_SIZE));
}

int Board::square_to_arr(char* str) {
    char row = str[1];
    char col = str[0];

    int remainder = col - 97;
    int quotient = ROW_SIZE - (row - '0');

    int out =  ROW_SIZE * quotient + remainder;
    if (out < 0 || out > 63) {
        cout << str << " is an incorrect square value" << endl;
        return -1;
    }

    return out;
}

char* Board::arr_to_square(int x) {
    if (x > 63) {
        cout << "the value must not be greater than 63" << endl;
        return nullptr;
    }

    char temp[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    int quotient = x / ROW_SIZE;
    int remainder = x % ROW_SIZE;

    char rank = (ROW_SIZE - quotient) + '0';
    char file = temp[remainder];

    char* out = (char*) malloc(sizeof(char) * 3);

    out[0] = file;
    out[1] = rank;
    out[2] = '\0';

    return out;
}

char* Board::get_piece_type(int x) {
    char* out = (char*) malloc(sizeof(char) * 10);
    switch(cells[x].piece.type) {
        case EMPTY: strcpy(out, "EMPTY"); break;
        case W_PAWN: strcpy(out, "W_PAWN"); break;
        case W_KNIGHT: strcpy(out, "W_KNIGHT"); break;
        case W_BISHOP: strcpy(out, "W_BISHOP"); break;
        case W_ROOK: strcpy(out, "W_ROOK"); break;
        case W_QUEEN: strcpy(out, "W_QUEEN"); break;
        case W_KING: strcpy(out, "W_KING"); break;
        case B_PAWN: strcpy(out, "B_PAWN"); break;
        case B_KNIGHT: strcpy(out, "B_KNIGHT"); break;
        case B_BISHOP: strcpy(out, "B_BISHOP"); break;
        case B_ROOK: strcpy(out, "B_ROOK"); break;
        case B_QUEEN: strcpy(out, "B_QUEEN"); break;
        case B_KING: strcpy(out, "B_KING"); break;
        }

    out[9] = '\0';
    return out;
}

void Board::get_valid_moves(int x, int* arr) {
    if (x == -1) {
        arr[0] = -1;
        return;
    }

    arr[0] = 0;

    if (!is_valid_square(x)) {
        cout << x << " is an invalid square" << endl;
        return;
    }

    switch(cells[x].piece.type) {
        case EMPTY: return;
        case W_PAWN: 
        {
            if (get_rank(x) == 2) {
                get_squares(x, 2, arr, NORTH);
            }

            int capture_coords[] = {x - 7, x - 9};
            if (is_valid_square(capture_coords[0]) && strcmp(get_piece_type(capture_coords[0]), "EMPTY") && get_rank(capture_coords[0]) != get_rank(x)) {
                get_squares(x, 1, arr, NORTH_EAST);
            }

            if (is_valid_square(capture_coords[1]) && strcmp(get_piece_type(capture_coords[1]), "EMPTY") && get_rank(capture_coords[1]) != get_rank(x)) {
                get_squares(x, 1, arr, NORTH_WEST);
            }
        }

break;
        case B_PAWN: break;


        case W_KNIGHT:
        case B_KNIGHT:
            get_squares(x, 1, arr, K_NORTH_EAST);
            get_squares(x, 1, arr, K_NORTH_WEST);
            get_squares(x, 1, arr, K_SOUTH_EAST);
            get_squares(x, 1, arr, K_SOUTH_WEST);
            get_squares(x, 1, arr, K_NORTH_NORTH_EAST);
            get_squares(x, 1, arr, K_NORTH_NORTH_WEST);
            get_squares(x, 1, arr, K_SOUTH_SOUTH_EAST);
            get_squares(x, 1, arr, K_SOUTH_SOUTH_WEST);
            break;

        case W_BISHOP:
        case B_BISHOP:
            get_squares(x, 8, arr, NORTH_EAST);
            get_squares(x, 8, arr, NORTH_WEST);
            get_squares(x, 8, arr, SOUTH_EAST);
            get_squares(x, 8, arr, SOUTH_WEST);
            break;

        case W_ROOK:
        case B_ROOK:
            get_squares(x, 8, arr, NORTH);
            get_squares(x, 8, arr, SOUTH);
            get_squares(x, 8, arr, EAST);
            get_squares(x, 8, arr, WEST);
            break;

        case W_QUEEN:
        case B_QUEEN:

        case W_KING:
        case B_KING: 
            {
                Direction dirs[] = {NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST};
                for (auto d : dirs) {
                 get_squares(x, 1, arr, d);
                }
                break;
            }
    }
}

void Board::get_squares(int start_square, int rank, int* square_lst, Direction dir) {
    if (rank < 1) {
        cout << "The rank must be at least one" << endl;
        return;
    }

    int val;
    int increment;

    switch (dir) {
        case NORTH: increment = -8; break;
        case SOUTH: increment = 8; break;
        case EAST: increment = 1; break;
        case WEST: increment = -1; break;
        case NORTH_EAST: increment = -7; break;
        case NORTH_WEST: increment = -9; break;
        case SOUTH_EAST: increment = 9; break;
        case SOUTH_WEST: increment = 7; break;
        case K_NORTH_EAST: increment = -6; break;
        case K_NORTH_WEST: increment = -10; break;
        case K_SOUTH_EAST: increment = 10; break;
        case K_SOUTH_WEST: increment = 6;
        case K_NORTH_NORTH_EAST: increment = -15; break;
        case K_NORTH_NORTH_WEST: increment = -17; break;
        case K_SOUTH_SOUTH_EAST: increment = 17; break;
        case K_SOUTH_SOUTH_WEST: increment = 15; break;
          break;
        }

    int size = square_lst[0];
    for (int i = 1; i <= rank; i++) {
        val = start_square + (increment * i);
        if (is_valid_square(val)) {
            square_lst[size + i] = val;
            square_lst[0]++;
        }
    }
}
