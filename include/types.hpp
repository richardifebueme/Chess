#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

typedef struct {
        const char* title;
        int win_x; int win_y;
        int win_w; int win_h;
} window_config;

enum GameState {
    IDLE,
    PIECE_SELECTED,
    PIECE_MOVE
};

enum Direction {
    NORTH = 0,
    SOUTH, EAST, WEST,

    NORTH_EAST, NORTH_WEST,
    SOUTH_EAST, SOUTH_WEST,

    K_NORTH_EAST, K_NORTH_WEST,
    K_SOUTH_EAST, K_SOUTH_WEST,

    K_NORTH_NORTH_EAST,
    K_NORTH_NORTH_WEST,

    K_SOUTH_SOUTH_EAST,
    K_SOUTH_SOUTH_WEST,
};

enum PieceType {
    EMPTY = 0,
    B_PAWN, W_PAWN, 
    B_KNIGHT, W_KNIGHT, 
    B_BISHOP, W_BISHOP, 
    B_ROOK, W_ROOK, 
    B_QUEEN, W_QUEEN, 
    B_KING, W_KING
};

enum Player {
    PLAYER_A,
    PLAYER_B,
};

struct ChessPiece {
    SDL_Texture* tex;
    SDL_Rect dst;
    SDL_Point pos;
    PieceType type;
    Player player;
    char square_notation[3];
};

struct Cell {
    ChessPiece piece;
    SDL_Rect rect;
};
