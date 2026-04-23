#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <iostream>
#include <math.h>

#include "RenderWindow.hpp"
#include "constants.hpp"
#include "types.hpp"

using namespace std;

RenderWindow::RenderWindow() {
    is_running = true;

    win = SDL_CreateWindow(win_desc.title, win_desc.win_x, win_desc.win_y, win_desc.win_w, win_desc.win_h, SDL_WINDOW_BORDERLESS);
    if (win == nullptr) {
        cout << "SDL_CreateWindow() Failed. Error: " << SDL_GetError() << endl;
        is_running = false;
    }

    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (rend == nullptr) {
        cout << "SDL_CreateRenderer() Failed. Error: " << SDL_GetError() << endl;
        is_running = false;
    }

    for (int i = 0; i < 64; i++) {
        if (board.cells[i].piece.type == EMPTY)
            board.cells[i].piece.tex = nullptr;
        else board.cells[i].piece.tex = load_piece_texture(board.cells[i].piece.type);
    }
}

SDL_Texture* RenderWindow::load_piece_texture(PieceType type) {
    SDL_Texture* tex;
    switch(type) {
        case EMPTY: break;
        case W_PAWN: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case W_KNIGHT: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case W_BISHOP: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case W_ROOK: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case W_QUEEN: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case W_KING: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case B_PAWN: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case B_KNIGHT: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case B_BISHOP: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case B_ROOK: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case B_QUEEN: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
        case B_KING: tex = IMG_LoadTexture(rend, "../res/images/pawn.png"); break;
    }

    return tex;
}

void RenderWindow::load_board() {
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(rend, 238, 195, 154, 255); // light cells
            } else {
                SDL_SetRenderDrawColor(rend, 143, 86, 59, 255); // dark cells
            }

            SDL_RenderFillRect(rend, &board.cells[i + j*ROW_SIZE].rect);

        }
    }
}

SDL_Texture* RenderWindow::load_texture(const char* filepath) {
    SDL_Texture* tex = IMG_LoadTexture(rend, filepath);
    if (tex == nullptr) {
        cout << "Failed to load texture" << endl;
    }

    return tex;
}

void RenderWindow::load_pieces() {
    for (int i = 0; i < 64; i++) {
        board.cells[i].piece.dst = {board.cells[i].rect.x, board.cells[i].rect.y, CELL_WIDTH, CELL_HEIGHT};
        SDL_RenderCopy(rend, board.cells[i].piece.tex, nullptr, &board.cells[i].piece.dst);
    }
}

void RenderWindow::render() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    load_board();
    load_pieces();

	SDL_RenderPresent(rend);
}

void RenderWindow::handle_inputs() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_q:
                    cout << "quitting" << endl;
					is_running = false;
					break;
			}
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int btn_coord = board.get_array_coord(event.button.x / CELL_WIDTH, event.button.y / CELL_HEIGHT);
                cout << board.get_piece_type(btn_coord) << endl;
            }
        }
	}
}

void RenderWindow::cleanUp() {
    for (int i = 0; i < 64; i++) {
        if (board.cells[i].piece.tex != nullptr) {
            SDL_DestroyTexture(board.cells[i].piece.tex);
            board.cells[i].piece.tex = nullptr;
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    IMG_Quit();
}
