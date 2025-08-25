#pragma once
#include <SDL2/SDL.h>
#include "util.h"

#define _STEPS_ 8

SDL_Surface* step_on;
SDL_Surface* step_off;
SDL_Surface* steps[_STEPS_];

void load_sequencer() { 
    step_on = SDL_LoadBMP("assets/sequencer/1.bmp");
    step_off = SDL_LoadBMP("assets/sequencer/0.bmp");
    for(int i = 0; i < _STEPS_; i++) {
        steps[i] = step_off;
    }
}

void render_sequencer() {
    SDL_Rect step_rect = {step_on->h,step_on->w,0,0};
    for(int i = 0; i < _STEPS_; i++) {
        SDL_BlitSurface(steps[i],NULL,win_surface,&step_rect);
        step_rect.x = step_rect.x + 10;
        if(i==7){step_rect.y = step_rect.y + 10; step_rect.x = step_rect.x - 60;}
    }

}

void free_sequencer() {
    for(int i = 0; i < _STEPS_; i++) {
        SDL_FreeSurface(steps[i]);
    }
}