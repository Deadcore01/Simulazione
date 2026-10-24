#include <stdio.h>
#include <SDL3/SDL.h>
#include "bsm.h"

void gestioneMenu(SDL_Event *e, gameState *stato) {
	if (e->type == SDL_EVENT_KEY_DOWN && e->key.key == SDLK_RETURN) {
		*stato = STATE_PLAYING;
	}
}

void gestioneGioco(SDL_Event *e, gameState *stato) {
	if (e->type == SDL_EVENT_KEY_DOWN) {
		if (e->key.key == SDLK_P) {
			*stato = STATE_PAUSED;
		} 
		else if (e->key.key == SDLK_ESCAPE) {
			*stato = STATE_EXIT;
		}
	}
}

void gestionePausa(SDL_Event *e, gameState *stato) {
	if (e->type == SDL_EVENT_KEY_DOWN && e->key.key == SDLK_R) {
		*stato = STATE_PLAYING;
	}
}


