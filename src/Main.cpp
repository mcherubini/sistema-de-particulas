//============================================================================
// Name        : Sistemas.cpp
// Author      : Michele
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char* argv[]) {

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL init failed" << endl;
		return 1;
	}
	//creamos la ventana
	SDL_Window *window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//si no se ha podido crear cerramos los recursos
	if (window == NULL) {
		SDL_Quit();
		return 2;
	}
	//creamos el objeto encargado de renderizar con sincronizacion vertical
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_PRESENTVSYNC);
	//creamos la textura que vamos a renderizar en la ventana
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		cout << "Could not create renderer" << endl;
		return 3;
	}

	if (texture == NULL) {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		cout << "Could not create texture" << endl;
		return 4;
	}

	//alojamos espacio de memoria para cada pixel que queremos modificar en nuestra ventana con un valor de 0 a 255(color)
	Uint32 * buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//asignamos el mismo valor al bloque de memoria que contiene el valor de cada pixel
	memset(buffer, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	bool quit = false;

	SDL_Event event;
	//actualizamos los pixeles con el valor de la textura
	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
	//reiniciamos el render actual
	SDL_RenderClear(renderer);
	//copiamos el valor de la textura actualizada al renderer
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	//actualiza la pantalla
	SDL_RenderPresent(renderer);
	while (!quit) {
		//actualizar particulas
		//pintar particulas
		//comprobar mensajes/eventos

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	delete[] buffer;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
