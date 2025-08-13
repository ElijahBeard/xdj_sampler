#pragma once
SDL_Surface *notes[10];
SDL_Surface *current_note;
SDL_Rect note_position;
SDL_Rect decoration_position;
int decoration = 0;

void load_notes() {
    notes[0] = SDL_LoadBMP("assets/keys/c.bmp");
    notes[1] = SDL_LoadBMP("assets/keys/d.bmp");
    notes[2] = SDL_LoadBMP("assets/keys/e.bmp");
    notes[3] = SDL_LoadBMP("assets/keys/f.bmp");
    notes[4] = SDL_LoadBMP("assets/keys/g.bmp");
    notes[5] = SDL_LoadBMP("assets/keys/a.bmp");
    notes[6] = SDL_LoadBMP("assets/keys/b.bmp");
    notes[7] = SDL_LoadBMP("assets/keys/flat.bmp");
    notes[8] = SDL_LoadBMP("assets/keys/sharp.bmp");
    notes[9] = SDL_LoadBMP("assets/keys/empty.bmp");
    for(int i = 0; i < 9; i++) {
        if(notes[i] == NULL) {
            printf("%s\n",SDL_GetError());
        }
    }
    current_note = notes[0];

    note_position.h = current_note->h;
    note_position.w = current_note->w;
    note_position.x = 1;
    note_position.y = 58;

    decoration_position.h = notes[8]->h;
    decoration_position.w = notes[8]->w;
    decoration_position.x = 5;
    decoration_position.y = 55;
}

void free_notes() {
    for(int i = 0; i < 9; i++) {
        SDL_FreeSurface(notes[i]);
    }
}