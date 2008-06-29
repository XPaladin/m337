#include "m337_engine.h"

m337_engine::~m337_engine()
{
}

void m337_engine::main_loop()
{
    bool close = false;
    SDL_Event event;
    while (!close) {
        repaint();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            close = true;
                            break;
                        case SDLK_UP:
                            move_unit(0, UP);
                            break;
                        case SDLK_RIGHT:
                            move_unit(0, RIGHT);
                            break;
                        case SDLK_DOWN:
                            move_unit(0, DOWN);
                            break;
                        case SDLK_LEFT:
                            move_unit(0, LEFT);
                            break;
                        case SDLK_w:
                            move_unit(1, UP);
                            break;
                        case SDLK_d:
                            move_unit(1, RIGHT);
                            break;
                        case SDLK_s:
                            move_unit(1, DOWN);
                            break;
                        case SDLK_a:
                            move_unit(1, LEFT);
                            break;
                        default:
                            break;
                    }
            }
        }
        SDL_Delay(game_tic);
    }
}


