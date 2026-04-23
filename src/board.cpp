#include <cstdlib>
#include <deque>
#include <iostream>
#include <string.h>

#include "board.hpp"
#include "constants.hpp"

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
            cells[i + (j*ROW_SIZE)].rect = {i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
        }
    }

    for (int i = 0; i < 64; i++) {
        strcpy(cells[i].piece.square_notation, arr_to_square(i));
    }
}

int Board::mouse_to_array(int x, int y) {
    return (x + (y*ROW_SIZE));
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

