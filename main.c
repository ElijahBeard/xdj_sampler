#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "util.h"
#include "notes.h"
#include "sampler.h"
#include "sequencer.h"
#include "knob.h"
#include "audio.h"
#include "load.h"

int running = 1;

int init() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf("%s",SDL_GetError());
        return 1;
    }

    if ( TTF_Init() < 0 ) {
        printf("%s",SDL_GetError());
        return 2;
    }

    if ( init_audio() != 0 ) {
        return 3;
    }

    window = SDL_CreateWindow(
        "xdj",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        _WIN_W_ * _SCALE_,_WIN_H_ * _SCALE_,SDL_WINDOW_BORDERLESS);
    if(!window) {
        printf("%s",SDL_GetError());
        return 4;
    }
    SDL_Surface* icon = SDL_LoadBMP("assets/icon.bmp");
    SDL_SetWindowIcon(window,icon);

    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer) {
        printf("%s",SDL_GetError());
        return 5;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");

    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_STREAMING,128,64);
    if (!texture) {
        printf("%s", SDL_GetError());
        return 6;
    }

    win_surface = SDL_CreateRGBSurfaceWithFormat(0,128,64,24,SDL_PIXELFORMAT_RGB24);
    if(!win_surface) {
        printf("%s",SDL_GetError());
        return 7;
    }

    SDL_FillRect(win_surface,NULL,SDL_MapRGB(win_surface->format,127,127,127));
    
    return 0;
}

void xdj_kill() {
    free_notes();
    free_sampler();
    free_sequencer();
    free_audio();
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
	SDL_Quit();
}

void load_assets() {
    // ASSETS BMP IMAGES
    font = TTF_OpenFont("assets/fonts/aurora-24.ttf", 7);
    if(!font){printf("%s",TTF_GetError());}
    skin = SDL_LoadBMP("assets/skin-nologo.bmp");
    load_notes();
    load_sampler();
    load_sequencer();
    load_ASDR();
}

void input(SDL_Event e) {
    while (SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                running=0;
            case SDL_KEYDOWN:
                if (e.key.repeat == 0) {
                    switch(e.key.keysym.sym) {
                        // NOTES
                            case SDLK_ESCAPE: running=0; break;
                            case SDLK_a:
                                note = 50 + (12 * oct);
                                note_on(note);
                                current_note = notes[0];
                                decoration = 0;
                                break;
                            case SDLK_w:
                                note = 51 + (12 * oct);
                                note_on(note);
                                current_note = notes[0];
                                decoration = 1;
                                break;
                            case SDLK_s:
                                note = 52 + (12 * oct);
                                note_on(note);
                                current_note = notes[1];
                                decoration = 0;
                                break;
                            case SDLK_e:
                                note = 53 + (12 * oct);
                                note_on(note);
                                current_note = notes[2];
                                decoration = 2;
                                break;
                            case SDLK_d:
                                note = 54 + (12 * oct);
                                note_on(note);
                                current_note = notes[2];
                                decoration = 0;
                                break;
                            case SDLK_f:
                                note = 55 + (12 * oct);
                                note_on(note);
                                current_note = notes[3];
                                decoration = 0;
                                break;
                            case SDLK_t:
                                note = 56 + (12 * oct);
                                note_on(note);
                                current_note = notes[3];
                                decoration = 1;
                                break;
                            case SDLK_g:
                                note = 57 + (12 * oct);
                                note_on(note);
                                current_note = notes[4];
                                decoration = 0;
                                break;
                            case SDLK_y:
                                note = 58 + (12 * oct);
                                note_on(note);
                                current_note = notes[5];
                                decoration = 2;
                                break;
                            case SDLK_h:
                                note = 59 + (12 * oct);
                                note_on(note);
                                current_note = notes[5];
                                decoration = 0;
                                break;
                            case SDLK_u:
                                note = 60 + (12 * oct);
                                note_on(note);
                                current_note = notes[6];
                                decoration = 2;
                                break;
                            case SDLK_j:
                                note = 61 + (12 * oct);
                                note_on(note);
                                current_note = notes[6];
                                decoration = 0;
                                break;
                            // loading
                            case SDLK_l:
                                load = 1;
                                load_state = load_btn[1];
                                SDL_StartTextInput();
                                break;
                            case SDLK_RETURN:
                                if(strlen(text) > 0) {
                                    load_new_sf(text);
                                }
                                load = 0;
                                SDL_StopTextInput();
                                break;
                            case SDLK_BACKSPACE:
                                if (strlen(text) > 0) {
                                    text[strlen(text) - 1] = '\0';
                                }
                                break;
                            // cursor
                            case SDLK_RIGHT:
                                if(cursor_pos.x < 128) {
                                    cursor_pos.x = cursor_pos.x + 2;
                                }
                                instrument++;
                                break;
                            case SDLK_LEFT:
                                if(cursor_pos.x > 0){
                                    cursor_pos.x = cursor_pos.x - 2;
                                }
                                if(instrument > 0){
                                    instrument--;
                                }
                                break;
                            case SDLK_UP:
                                oct++;
                                BPM++;
                                break;
                            case SDLK_DOWN:
                                oct--;
                                BPM--;
                                break;
                            // knobs
                            case SDLK_z:
                                tune += 0.1f;
                                tsf_channel_set_tuning(g_sf,0,tune);
                                rotate_knob(&A_rect,A = A + .3);
                                break;
                            case SDLK_x:
                                tune -= 0.1f;
                                tsf_channel_set_tuning(g_sf,0,tune);
                                rotate_knob(&A_rect,A = A - .3);
                                break;
                            case SDLK_c:
                                rotate_knob(&D_rect,D = D + .3);
                                break;
                            case SDLK_v:
                                rotate_knob(&R_rect,R = R + .3);
                                break;
                            default:
                                break;
                    }
                }
                break;
            case SDL_KEYUP:
                switch(e.key.keysym.sym) {
                    case SDLK_l:load_state = load_btn[0];break;
                    case SDLK_a:tsf_note_off_all(g_sf);break;
                    case SDLK_s:tsf_note_off_all(g_sf);break;
                    case SDLK_d:tsf_note_off_all(g_sf);break;
                    case SDLK_f:tsf_note_off_all(g_sf);break;
                    case SDLK_g:tsf_note_off_all(g_sf);break;
                }
                break;
            case SDL_TEXTINPUT:
                strncat(text, e.text.text, TEXT_MAX - strlen(text) - 1);
                break;
            case SDL_TEXTEDITING:
                strncpy(composition, e.edit.text, TEXT_MAX - 1);
                composition[TEXT_MAX - 1] = '\0';
                cursor_text = e.edit.start;
                selection_len = e.edit.length;
                break;
        }
    }
}

void render() {
    SDL_BlitSurface(skin, NULL, win_surface, NULL);
    render_notes();
    render_sequencer();
    render_ASDR();
    render_live_waveform();
    SDL_BlitSurface(cursor,NULL,win_surface,&cursor_pos);
    SDL_BlitSurface(load_state,NULL,win_surface,&load_pos);
    // scaling
    SDL_UpdateTexture(texture,NULL,win_surface->pixels,win_surface->pitch);
    SDL_RenderCopy(renderer,texture,NULL,NULL);

    SDL_Rect dst = {0, 0, _WIN_W_ * _SCALE_, _WIN_H_ * _SCALE_};
    SDL_RenderCopy(renderer, waveform, NULL, &dst); // waveform
    SDL_RenderCopy(renderer, asdr, NULL, NULL);
    
    if(load) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer,0,0,0,128);
        SDL_Rect r = {0,0,_WIN_W_*_SCALE_,_WIN_H_*_SCALE_};
        SDL_RenderFillRect(renderer,&r);
        render_load();
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

int main(int argc, char** args) {
    if(init() != 0) {perror("Init Failed\n"); return 1;}
    load_assets();
    SDL_AddTimer(60000 / BPM,step,NULL);
    
    SDL_Event e;
    while(running == 1)
    {
        input(e);
        render();
    }

    xdj_kill();

    return 0;
}