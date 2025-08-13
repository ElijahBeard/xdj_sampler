#pragma once
#include <SDL2/SDL.h>

SDL_Surface *cursor;
SDL_Rect cursor_pos;

SDL_Surface *load_btn[2];
SDL_Surface *load_state;
SDL_Rect load_pos;

SDL_AudioSpec spec;
Uint32 wlength;
Uint8 *buffer;

void load_sampler() {
    cursor = SDL_LoadBMP("assets/cursor.bmp");
    cursor_pos.h = cursor->h;
    cursor_pos.w = cursor->w;
    cursor_pos.x = 0;
    cursor_pos.y = 23;

    load_btn[0] = SDL_LoadBMP("assets/load.bmp");
    load_btn[1] = SDL_LoadBMP("assets/load_sel.bmp");
    load_pos.h = load_btn[0]->h;
    load_pos.w = load_btn[0]->w;
    load_pos.x = 107;
    load_pos.y = 51;
    
    load_state = load_btn[0];

    // audio part
    if(SDL_LoadWAV("assets/audio/test.wav",&spec,&buffer,&wlength) == NULL)
        printf("%s\n",SDL_GetError());
}

void free_sampler() {
    SDL_FreeWAV(buffer);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(load_btn[0]);
    SDL_FreeSurface(load_btn[1]);
}

