#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <time.h>
#include <string.h>
#include "config.h"
#include "finestra.h"
#include "bsm.h"

int running = FALSE;

SDL_Window *pFinestra = NULL;
SDL_Renderer *pRenderer = NULL;
gameState stato = STATE_MENU;

TTF_Font *font = NULL;

struct Creatura {
	float velX;
	float velY;
	float x;
	float y;
	int w;
	int h;
};
struct Creatura creatura1 = {60.0f, 60.0f, 100.0f, 100.0f, 20, 20};

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
// esc
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE) {
					running = FALSE;
				}
				break;
		}
		if (event.type == SDL_EVENT_QUIT) {
			stato = STATE_EXIT;
		}
		switch (stato) {
			case STATE_MENU:
				gestioneMenu(&event, &stato);
				break;
			case STATE_PLAYING:
				gestioneGioco(&event, &stato);
				break;
			case STATE_PAUSED:
				gestionePausa(&event, &stato);
				break;
			default:
				break;

		}
		if (stato == STATE_EXIT) {
			running = FALSE;
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
	Uint64 deltaTime = aggiornaTempo();
	float sec = deltaTime /1000.0f ;
	creatura1.x += creatura1.velX * sec;
	creatura1.y += creatura1.velY * sec;

//bound check bordi
	if (creatura1.x <= 0) {
		creatura1.x = 0;
		creatura1.velX = -creatura1.velX;
	}
	if (creatura1.x + creatura1.w >= X_FINESTRA) {
		creatura1.x = X_FINESTRA - creatura1.w;
		creatura1.velX = -creatura1.velX;

	}
	if (creatura1.y <= 0) {
		creatura1.y = 0;
		creatura1.velY = -creatura1.velY;
	}
	if (creatura1.y + creatura1.h >= Y_FINESTRA) {
		creatura1.y = Y_FINESTRA - creatura1.h;
		creatura1.velY = -creatura1.velY;
	}
}
 
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, float x, float y) {
	SDL_Color bianco = {255, 255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, strlen(text), bianco);
	if (!surface) return;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture) { 
		SDL_DestroySurface(surface);
		return;
	}
	SDL_FRect dst = {x,y, (float)surface->w,(float)surface->h};
SDL_RenderTexture(renderer, texture, NULL, &dst);
SDL_DestroyTexture(texture);
SDL_DestroySurface(surface);
}


void render() {
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer);
	switch (stato){
		case STATE_MENU:
			render_text(pRenderer, font, "premi ENTER per iniziare", 50, 50);
			break;

		case STATE_PLAYING: {
			render_text(pRenderer, font, "premi P per mettere in pausa, Esc per uscire", 50, 50);
			SDL_FRect entità = {
				creatura1.x,
				creatura1.y,
				(float)creatura1.w,
				(float)creatura1.h
			};
			SDL_SetRenderDrawColor(pRenderer, 50, 220, 100, 255);
			SDL_RenderFillRect(pRenderer, &entità);
			break; }
		case STATE_PAUSED:
			render_text(pRenderer, font, "In Pausa... premi R per continuare, Esc per uscire", 50, 50);
			break;
	
		default:
			break;
	}
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

	if (!TTF_Init()) {
    		fprintf(stderr, "Errore inizializzazione SDL_ttf: %s\n", SDL_GetError());
    		distruggiFinestra(pRenderer, pFinestra);
   		return 1;
}

	font = TTF_OpenFont("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf", 24.0f);

	if (font == NULL) {
    		fprintf(stderr, "Errore caricamento font: %s\n", SDL_GetError());
    		TTF_Quit();
   		 distruggiFinestra(pRenderer, pFinestra);
    		return 1;
}
	
// GAME LOOP
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
