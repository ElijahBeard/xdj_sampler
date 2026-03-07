#pragma once
#include <SDL2/SDL.h>
#include "math.h"
#include "util.h"

SDL_Rect A_rect, S_rect, D_rect, R_rect;
SDL_Texture *asdr;
float A=90,S=90,D=90,R=90;

void render_ASDR(){
    SDL_SetRenderTarget(renderer,asdr);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, A_rect.x, A_rect.y, A_rect.w, A_rect.h);
    SDL_RenderDrawLine(renderer, S_rect.x, S_rect.y, S_rect.w, S_rect.h);
    SDL_RenderDrawLine(renderer, D_rect.x, D_rect.y, D_rect.w, D_rect.h);
    SDL_RenderDrawLine(renderer, R_rect.x, R_rect.y, R_rect.w, R_rect.h);

    SDL_SetRenderTarget(renderer, NULL);
}

void rotate_knob(SDL_Rect* knob,float theta) {
    int w = knob->x + (int)(_KNOB_LEN_ * cos(theta));
    int h = knob->y + (int)(_KNOB_LEN_ * sin(theta));
    knob->w = w;
    knob->h = h;
    if(debug)
        printf("Rot Knob %f : (%d,%d)\n",A,w,h);

}

void load_ASDR(){
    asdr = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        _WIN_W_,
        _WIN_H_
    );
    SDL_SetTextureBlendMode(asdr, SDL_BLENDMODE_BLEND);
    A_rect.x = 9, A_rect.y = 14;
    A_rect.w = 9, A_rect.h = 10;

    S_rect.x = 25, S_rect.y = 14;
    S_rect.w = 25, S_rect.h = 10;

    D_rect.x = 41, D_rect.y = 14;
    D_rect.w = 41, D_rect.h = 10;

    R_rect.x = 57, R_rect.y = 14;
    R_rect.w = 57, R_rect.h = 10;
}