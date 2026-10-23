#include <stdio.h>
#include <SDL3/SDL.h>
#include "finestra.h"
#include "config.h"


int initFinestra(void) {
	if (SDL_Init(SDL_INIT_VIDEO) == FALSE){
		fprintf(stderr, "errore inizializzazione SDL: %s\n", SDL_GetError());
		return FALSE;
	}
	return TRUE;
}

SDL_Window *creaFinestra(void) {
	SDL_Window *pFinestra = SDL_CreateWindow(
		"simulation",
		X_FINESTRA,
		Y_FINESTRA,
		0
	);
	if (!pFinestra) {
		fprintf(stderr, "errore creazione SDL: %s\n", SDL_GetError());
		return NULL;
	}
return pFinestra;
}

SDL_Renderer *creaRenderer(SDL_Window *pFinestra) {
	SDL_Renderer *pRenderer = SDL_CreateRenderer(pFinestra, NULL);
	if (!pRenderer) {
		fprintf(stderr, "errore creazione SDL renderer: %s\n", SDL_GetError());
		return NULL;
	}
	return pRenderer;
}

void distruggiFinestra(SDL_Renderer *pRenderer,
		SDL_Window *pFinestra) {
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pFinestra);
	SDL_Quit();
}

