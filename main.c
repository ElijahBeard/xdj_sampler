#include <SDL2/SDL.h>
#include "util.h"
#include "notes.h"
#include "sampler.h"
#include "sequencer.h"

int running = 1;

int init() {
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf("%s",SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "xdj",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        _WIN_W_ * _SCALE_,_WIN_H_ * _SCALE_,SDL_WINDOW_BORDERLESS);
    if(!window) {
        printf("%s",SDL_GetError());
        return 1;
    }
    SDL_Surface* icon = SDL_LoadBMP("assets/icon.bmp");
    SDL_SetWindowIcon(window,icon);

    renderer = SDL_CreateRenderer(window,-1,0);
    if(!renderer) {
        printf("%s",SDL_GetError());
        return 1;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");

    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_STREAMING,128,64);
    if (!texture) {
        printf("%s", SDL_GetError());
        return 1;
    }

    win_surface = SDL_CreateRGBSurfaceWithFormat(0,128,64,24,SDL_PIXELFORMAT_RGB24);
    if(!win_surface) {
        printf("%s",SDL_GetError());
        return 1;
    }

    SDL_FillRect(win_surface,NULL,SDL_MapRGB(win_surface->format,127,127,127));
    
    return 0;
}

void kill() {
    free_notes();
    free_sampler();
    free_sequencer();
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
	SDL_Quit();
}

void load_assets() {
    // ASSETS BMP IMAGES
    skin = SDL_LoadBMP("assets/skin-nologo.bmp");
    load_notes();
    load_sampler();
    load_sequencer();
}

void input(SDL_Event e) {
    while (SDL_PollEvent(&e) != 0) {
    switch(e.type) {
        case SDL_QUIT:
            running=0;
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym) {
                // NOTES
                    case SDLK_q:
                        running=0;
                        break;
                    case SDLK_a:
                        current_note = notes[0];
                        decoration = 0;
                        break;
                    case SDLK_w:
                        current_note = notes[0];
                        decoration = 1;
                        break;
                    case SDLK_s:
                        current_note = notes[1];
                        decoration = 0;
                        break;
                    case SDLK_e:
                        current_note = notes[2];
                        decoration = 2;
                    case SDLK_d:
                        current_note = notes[2];
                        decoration = 0;
                        break;
                    case SDLK_f:
                        current_note = notes[3];
                        decoration = 0;
                        break;
                    case SDLK_t:
                        current_note = notes[3];
                        decoration = 1;
                        break;
                    case SDLK_g:
                        current_note = notes[4];
                        decoration = 0;
                        break;
                    case SDLK_y:
                        current_note = notes[5];
                        decoration = 2;
                        break;
                    case SDLK_h:
                        current_note = notes[5];
                        decoration = 0;
                        break;
                    case SDLK_u:
                        current_note = notes[6];
                        decoration = 2;
                        break;
                    case SDLK_j:
                        current_note = notes[6];
                        decoration = 0;
                        break;
                    case SDLK_l:
                        load_state = load_btn[1];
                        printf("state1\n");
                        break;
                    // cursor
                    case SDLK_RIGHT:
                        if(cursor_pos.x < 128) {
                            cursor_pos.x = cursor_pos.x + 2;
                        }
                        break;
                    case SDLK_LEFT:
                        if(cursor_pos.x > 0){
                            cursor_pos.x = cursor_pos.x - 2;
                        }
                        break;
                    case SDLK_UP:
                        if(zoom < 0) {
                            zoom = zoom + 1;
                        }
                        break;
                    case SDLK_DOWN:
                        zoom = zoom - 1;
                        break;
            }
        case SDL_KEYUP:
            switch(e.key.keysym.sym) {
                case SDLK_l:
                    load_state = load_btn[0];
                    printf("state0\n");
                    break;
            }
    }
}
}

void render() {
    SDL_BlitSurface(skin, NULL, win_surface, NULL);
    // notes + decorations
    render_notes();
    // cursor
    SDL_BlitSurface(cursor,NULL,win_surface,&cursor_pos);

    // button
    SDL_BlitSurface(load_state,NULL,win_surface,&load_pos);

    //seq
    render_sequencer();

    // waveform
    generate_waveform();
    SDL_UpdateTexture(texture,NULL,win_surface->pixels,win_surface->pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_Rect dst = {0, 0, _WIN_W_ * _SCALE_, _WIN_H_ * _SCALE_};
    SDL_RenderCopy(renderer, waveform, NULL, &dst);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

int main(int argc, char** args) {
    init();
    load_assets();
    SDL_AddTimer(60000 / BPM,step,NULL);
    
    SDL_Event e;
    while(running == 1)
    {
        input(e);
        render();
    }

    kill();

    return 0;
}