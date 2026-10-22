#ifndef FINESTRA_H
#define FINESTRA_H

#include <SDL3/SDL.h>

int initFinestra(void);

SDL_Window *creaFinestra(void);

SDL_Renderer *creaRenderer(SDL_Window *pFinestra);

void distruggiFinestra(SDL_Renderer *pRenderer,
	SDL_Window *pFinestra);
#endif
