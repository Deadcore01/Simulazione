#ifndef BSM_H
#define BSM_H

#include <SDL3/SDL.h>

typedef enum {
	STATE_MENU,
	STATE_PLAYING,
	STATE_PAUSED,
	STATE_EXIT
} gameState;


void gestioneMenu(SDL_Event *e, gameState *stato);

void gestioneGioco(SDL_Event *e, gameState *stato);

void gestionePausa(SDL_Event *e, gameState *stato);

#endif
