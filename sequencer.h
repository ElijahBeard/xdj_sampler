#pragma once
#include <SDL2/SDL.h>
#include "util.h"

#define _STEPS_ 8

SDL_Surface* step_on;
SDL_Surface* step_off;
SDL_Surface* steps[_STEPS_];
uint8_t current_step = 0;

void load_sequencer() { 
    step_on = SDL_LoadBMP("assets/sequencer/1.bmp");
    step_off = SDL_LoadBMP("assets/sequencer/0.bmp");
    for(int i = 0; i < _STEPS_; i++) {
        steps[i] = step_off;
    }
}

void render_sequencer() {
    SDL_Rect step_rect = {20,50,step_on->h,step_on->w};
    for(int i = 0; i < _STEPS_; i++) {
        if(i == current_step) {
            steps[i] = step_on;
        } else {
            steps[i] = step_off;
        }
        SDL_BlitSurface(steps[i],NULL,win_surface,&step_rect);
        step_rect.x = step_rect.x + 10;
        if(i==7){step_rect.y = step_rect.y + 10; step_rect.x = step_rect.x - 60;}
    }
    if(current_step == _STEPS_) current_step = 0;
}

Uint32 step(Uint32, void*) {
    current_step++;
    return 60000 / BPM;
}

void free_sequencer() {
    // for(int i = 0; i < _STEPS_; i++) {
    //     SDL_FreeSurface(steps[i]);
    // }
    SDL_FreeSurface(step_on);
    SDL_FreeSurface(step_off);
}