#pragma once
#include "SDL2/SDL.h"

SDL_Window* window = NULL;
SDL_Surface* win_surface = NULL;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Surface* skin = NULL;
int zoom = 0;

#define _WIN_W_ 128
#define _WIN_H_ 64
#define _SCALE_ 5

void load_and_blit(SDL_Surface* surface,int x,int y) {
    SDL_Rect tmp_rect = {surface->w,surface->h,x,y};
}