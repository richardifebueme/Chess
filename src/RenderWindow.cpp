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
        if (board.cells[i].piece.type == EMPTY)
            board.cells[i].piece.tex = nullptr;
        else board.cells[i].piece.tex = load_piece_texture(board.cells[i].piece.type);
    }

    for (int i = 0; i < 64; i++) {
        board.cells[i].piece.dst = {board.cells[i].rect.x, board.cells[i].rect.y, CELL_WIDTH, CELL_HEIGHT};
        SDL_RenderCopy(rend, board.cells[i].piece.tex, nullptr, &board.cells[i].piece.dst);
    }
}

void RenderWindow::display_valid_moves(int square) {
    if (!board.is_empty_at(square)) {
        // SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
        // SDL_SetRenderDrawColor(rend, 0, 0, 0, 100); // semi-transparent
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        // get valid moves
        int moves_arr[28];
        board.get_valid_moves(square, moves_arr);

        int size = moves_arr[0];
        if (size == -1) return;

        // for each move in valid moves, render valid moves on the board
        for (int i = 1; i <= size; i++) {
            SDL_Rect rect = board.cells[moves_arr[i]].rect;

            SDL_RenderFillRect(rend, &rect);
        }
    }
}

void RenderWindow::render() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    load_board();
    load_pieces();

    // if (selected_square != -1) {
    //     display_valid_moves(selected_square);
    // }

    switch (state) {
    case IDLE:
        if (last_clicked != -1) {
            selected_square = last_clicked;
            last_clicked = -1;
            state = PIECE_SELECTED;
        }
        break;

    case PIECE_SELECTED:
        display_valid_moves(selected_square);
        if (last_clicked != -1) {
            if (board.is_valid_move(selected_square, last_clicked)) {
                board.move_piece(selected_square, last_clicked);
                selected_square = -1;
                last_clicked = -1;
            } 
            state = IDLE;
        }
        break;

    case PIECE_MOVE:
        // animations... someday
        state = IDLE;
        break;
    }

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
                last_clicked = board.mouse_to_array(event.button.x, event.button.y);
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                int btn_coord = board.mouse_to_array(event.button.x, event.button.y);
                cout << btn_coord << endl;
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
