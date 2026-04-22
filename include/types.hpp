#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

typedef struct {
        const char* title;
        int win_x; int win_y;
        int win_w; int win_h;
} window_config;


enum PieceType {
    EMPTY = 0,
    W_PAWN, W_KNIGHT, W_BISHOP,
    W_ROOK, W_QUEEN, W_KING,
    B_PAWN, B_KNIGHT, B_BISHOP,
    B_ROOK, B_QUEEN, B_KING,
};

struct ChessPiece {
    SDL_Texture* tex;
    SDL_Rect dst;
    SDL_Point pos;
    PieceType type;
};

struct Cell {
    ChessPiece piece;
    SDL_Rect rect;
};

// // 0 - 12
// enum Piece {
//     NIL,
//     W_PAWN, W_BISHOP, W_KNIGHT, W_ROOK, W_QUEEN, W_KING,
//     B_PAWN, B_BISHOP, B_KNIGHT, B_ROOK, B_QUEEN, B_KING
// };
//
// class Board {
// public:
//     Board() = default;
//
// private:
//     Piece cells[8][8] = {
//         {B_ROOK, B_KNIGHT, B_BISHOP, B_KING, B_QUEEN, B_BISHOP, B_KNIGHT, B_ROOK},
//         {B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN},
//         {NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
//         {NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
//         {NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
//         {NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
//         {W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN},
//         {W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK},
//     };
// };
