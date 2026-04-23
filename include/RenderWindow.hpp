#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_video.h>

#include "board.hpp"
#include "constants.hpp"
#include "types.hpp"


class RenderWindow {
    private:
        SDL_Window* win = nullptr;
        SDL_Renderer* rend = nullptr;
        Board board;
        window_config win_desc = {"CHESS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT};
        bool is_running;
    public:
        RenderWindow();
        void load_board();
        SDL_Texture* load_texture(const char* filepath);
        void load_pieces();
        SDL_Texture* load_piece_texture(PieceType type);
        void render();
        void handle_inputs();
        void cleanUp();
        bool isRunning() { return is_running; }
};
