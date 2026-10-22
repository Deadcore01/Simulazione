#include <stdio.h>
#include <SDL3/SDL.h>
#include <time.h>
#include "config.h"
#include "finestra.h"

int running = FALSE;

SDL_Window *pFinestra = NULL;
SDL_Renderer *pRenderer = NULL;

//inizializza il video

//crea finestra

//crea il renderer

struct Creatura {
	float vel;
	float x;
	float y;
	int w;
	int h;
};
struct Creatura creatura1 = {60.0f, 100.0f, 100.0f, 20, 20};

void setup(void) {
	pFinestra = creaFinestra();
	if (pFinestra == NULL) {
		running = FALSE;
		return;
	}
	pRenderer = creaRenderer(pFinestra);
	if(pRenderer == NULL) {
		SDL_DestroyWindow(pFinestra);
		pFinestra = NULL;
		running = FALSE;
		return;
	}
}

void process_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				running = FALSE;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE) {
					running = FALSE;
				}
				break;
		}
	}
}

Uint64 aggiornaTempo(void) {
	static Uint64 ultimoTick = 0;
	Uint64 tempoAttuale = SDL_GetTicks();
	if(ultimoTick == 0) {
	ultimoTick = tempoAttuale;
	return FALSE;
	}
	Uint64 deltaTime = tempoAttuale - ultimoTick;
	ultimoTick = tempoAttuale;
	return deltaTime;

}

void update() {
	//DA FARE:
	Uint64 deltaTime = aggiornaTempo();
	float sec = deltaTime /1000.0f ;
	creatura1.x += creatura1.vel * sec;
	creatura1.y += creatura1.vel * sec;
	if (creatura1.x > X_FINESTRA - creatura1.w) {
		creatura1.x = 0;
	}
	if  (creatura1.y > Y_FINESTRA - creatura1.h) {
		creatura1.y = 0;
	}

}

void render() {
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer);
	SDL_FRect entità = {
		creatura1.x,
		creatura1.y,
		(float)creatura1.w,
		(float)creatura1.h
	};
	SDL_SetRenderDrawColor(pRenderer, 50, 220, 100, 255);
	SDL_RenderFillRect(pRenderer, &entità);
	SDL_RenderPresent(pRenderer);
}

int main (void) {
//	SDL_Window *pFinestra = NULL;
//	SDL_Renderer *pRenderer = NULL;
	running = initFinestra();
	setup();
	if (!running) {
		fprintf(stderr, "errore: creazione finestra o renderer fallita\n");
		return FALSE;
	}
	printf("finestra creata\n");
	while (running) {
		Uint64 inizioFrame = SDL_GetTicks();
		process_input();
		update();
		render();
		Uint64 tempoFrame = SDL_GetTicks() - inizioFrame;
		if (tempoFrame < DURATA_FRAME) {
		SDL_Delay((Uint32)(DURATA_FRAME - tempoFrame));
		}
	}
	distruggiFinestra(pRenderer, pFinestra);
	return 0;
}
