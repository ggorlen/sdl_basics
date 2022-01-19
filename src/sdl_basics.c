#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

const int WINDOW_W = 640;
const int WINDOW_H = 480;
const float PI = 3.141592653589793;

int main(int argc, char **args) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "hello sdl",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_W,
        WINDOW_H,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    //SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    int mouseX = 0;
    int mouseY = 0;

    for (;;) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);

        for (SDL_Event e; SDL_PollEvent(&e);) {
            if (e.type == SDL_QUIT || 
                    (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                goto end_main_loop;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                     //e.type == SDL_MOUSEBUTTONDOWN ||
                     //e.type == SDL_MOUSEBUTTONUP) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }
        }
        
        int r = 15;//rand() % 256;
        int g = 150;//rand() % 256;
        int b = 150;//rand() % 256;
        SDL_SetRenderDrawColor(renderer, r, g, b, 200);

        //for (int i = 0; i < 10; i++) {
        //    SDL_RenderDrawPoint(renderer, mouseX - i, mouseY + i);
        //}

        int radius = 80;
        float lastX = mouseX + cos(0) * radius;
        float lastY = mouseY + sin(0) * radius;

        for (int a = 0; a <= 360; a += 30) {
            float xx = mouseX + cos(a * PI / 180) * radius;
            float yy = mouseY + sin(a * PI / 180) * radius;
            SDL_RenderDrawLine(renderer, lastX, lastY, xx, yy);
            lastX = xx;
            lastY = yy;
        }

        //SDL_Rect rect = {mouseX, mouseY, 100, 50};
        //SDL_RenderFillRect(renderer, &rect);
        //SDL_RenderDrawRect(renderer, &rect);

        //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0xFF, 0xFF));
        //SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);
    }

end_main_loop:
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

