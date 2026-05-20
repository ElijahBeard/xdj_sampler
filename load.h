#include "util.h"
#include "audio.h"
#include "soundfont/miniaudio_io.h"
#include "soundfont/tsf.h"

#define TEXT_MAX 256
int load = 0;
char text[TEXT_MAX] = "";
char composition[TEXT_MAX] = "";
Sint32 selection_len;
Sint32 cursor_text;

int load_sf() {
    ma_mutex_lock(&g_mutex);
    g_sf = tsf_load_filename(text);
    if (!g_sf) {
        printf("Couldn't Load SoundFont\n");
        g_sf = tsf_load_filename(sound_font_path);
    }
    ma_mutex_unlock(&g_mutex);
    return 0;
}

void render_load() {
    if(strlen(text) == 0) return;

    SDL_Color color = {255,255,255,255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, text, color);
    if(!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    int text_w = surf->w * 5;
    int text_h = surf->h * 5;
    SDL_SetTextureScaleMode(tex, SDL_ScaleModeNearest);


    SDL_FreeSurface(surf);

    int screen_w = _WIN_W_ * _SCALE_;
    int screen_h = _WIN_H_ * _SCALE_;

    int pad = 12;

    SDL_Rect box = {
        (screen_w - (text_w + pad*2))/2,
        (screen_h - (text_h + pad*2))/2,
        text_w + pad*2,
        text_h + pad*2
    };

    SDL_Rect text_rect = {
        box.x + pad,
        box.y + pad,
        text_w,
        text_h
    };

    SDL_SetRenderDrawColor(renderer,0,0,0,220);
    SDL_RenderFillRect(renderer,&box);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawRect(renderer,&box);

    SDL_RenderCopy(renderer,tex,NULL,&text_rect);

    SDL_DestroyTexture(tex);
}

// // void render_bpm() {
//     char bpm_text[16];
//     snprintf(bpm_text,sizeof(bpm_text),"%d",BPM);
//     SDL_Color text_color = {255, 255, 255};
//     SDL_Surface* text = TTF_RenderText_Solid(font, bpm_text, text_color);
//     if(!text){printf("%s\n", TTF_GetError());}
//     SDL_Rect dest = { 54, 52, text->w, text->h };
//     SDL_BlitSurface(text, NULL, win_surface, &dest);
//     SDL_Rect bmp_rect = { 46,57,met->w,met->h };
//     SDL_BlitSurface(met,NULL,win_surface,&bmp_rect);
//     SDL_FreeSurface(text);
// }