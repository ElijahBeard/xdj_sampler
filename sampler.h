#pragma once
#include <SDL2/SDL.h>
#include "util.h"

SDL_Surface *cursor;
SDL_Rect cursor_pos;

SDL_Surface *load_btn[2];
SDL_Surface *load_state;
SDL_Rect load_pos;

SDL_AudioSpec spec;
Uint32 wav_length;
Uint8 *wav_buffer;

SDL_Texture *waveform;


void generate_waveform() {
    int multiplier = 1000;
    int mid_y = _WIN_H_ / 2 + 1;
    int pixel_length = round(wav_length / _WIN_W_ + zoom);
    
    double tmp[wav_length];
    for (int i = 0; i < wav_length; i++) tmp[i] = wav_buffer[i] / 32768.0;
    
    SDL_Rect clear_rect = {0, 23, 128, 45};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &clear_rect);
    SDL_SetRenderTarget(renderer, waveform);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    for(int x = 0; x < _WIN_W_; x++) {
        double val = tmp[x * pixel_length];
        // printf("%d:%f\n",i,(wav_data[i] * multiplier));
        int y_neg = mid_y - (val * multiplier);
        int y_pos = mid_y + (val * multiplier);
        SDL_RenderDrawLine(renderer, x, mid_y, x, y_pos);
        SDL_RenderDrawLine(renderer, x, mid_y, x, y_neg);
    }
    SDL_SetRenderTarget(renderer, NULL);
}

void load_sampler() {
    waveform = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,_WIN_W_,_WIN_H_);
    SDL_SetTextureBlendMode(waveform, SDL_BLENDMODE_BLEND);
    cursor = SDL_LoadBMP("assets/cursor.bmp");
    cursor_pos.h = cursor->h;
    cursor_pos.w = cursor->w;
    cursor_pos.x = 0;
    cursor_pos.y = 22;

    load_btn[0] = SDL_LoadBMP("assets/load.bmp");
    load_btn[1] = SDL_LoadBMP("assets/load_sel.bmp");
    load_pos.h = load_btn[0]->h;
    load_pos.w = load_btn[0]->w;
    load_pos.x = 107;
    load_pos.y = 51;
    
    load_state = load_btn[0];

    // audio part
    if(SDL_LoadWAV("assets/audio/clap_max.wav",&spec,&wav_buffer,&wav_length) == NULL)
        printf("%s\n",SDL_GetError());
}


void free_sampler() {
    SDL_FreeWAV(wav_buffer);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(load_btn[0]);
    SDL_FreeSurface(load_btn[1]);
}

