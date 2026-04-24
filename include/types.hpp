#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

typedef struct {
        const char* title;
        int win_x; int win_y;
        int win_w; int win_h;
} window_config;

enum Direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_EAST,
    SOUTH_WEST,
    K_NORTH_EAST,
    K_NORTH_WEST,
    K_SOUTH_EAST,
    K_SOUTH_WEST,
    K_NORTH_NORTH_EAST,
    K_NORTH_NORTH_WEST,
    K_SOUTH_SOUTH_EAST,
    K_SOUTH_SOUTH_WEST,
};

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
    char square_notation[3];
};

struct Cell {
    ChessPiece piece;
    SDL_Rect rect;
};
