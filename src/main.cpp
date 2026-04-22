#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_timer.h>
#include <iostream>

#include "RenderWindow.hpp"

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        cout << "SDL_Init() Failed. Error: " << SDL_GetError() << endl;
    }

    if(!IMG_Init(IMG_INIT_PNG)) {
        cout << "IMG_Init() Failed. Error: " << SDL_GetError() << endl;
    }

    RenderWindow win;

    while (win.isRunning()) {
	    win.render();
	    win.handle_inputs();
	    SDL_Delay(30);
    }

    win.cleanUp();
    SDL_Quit();
    return 0;
}
