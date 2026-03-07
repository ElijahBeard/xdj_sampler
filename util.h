#pragma once
#include "SDL2/SDL.h"

int debug = 1;

SDL_Window* window;
SDL_Surface* win_surface;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Surface* skin;
TTF_Font* font;
int zoom = 0;

Uint32 ticks = 0, last_ticks, elapsed;
Uint16 BPM = 120;

#define _WIN_W_ 128
#define _WIN_H_ 64
#define _SCALE_ 5
#define _KNOB_LEN_ 5

void load_and_blit(SDL_Surface* surface,int x,int y) {
    SDL_Rect tmp_rect = {surface->w,surface->h,x,y};
}