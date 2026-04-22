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
        strcpy(cells[i].piece.square_notation, get_square_notation(i));
    }
}

int Board::get_array_coord(int x, int y) {
    return (x + (y*ROW_SIZE));
}

char* Board::get_square_notation(int x) {
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

