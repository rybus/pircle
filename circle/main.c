#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "store.h"

void pause();

#define WINDOW_LENGTH 1000

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    double a;
    int number_of_prime_to_display = 0;
    prime * last_prime = NULL;

    SDL_Point window_position = {
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED};
    SDL_Point center = {
        WINDOW_LENGTH / 2,
        WINDOW_LENGTH / 2};

    SDL_Point window_size = {WINDOW_LENGTH, WINDOW_LENGTH};
    SDL_Color blue = {0, 120, 199};

    SDL_Init(SDL_INIT_VIDEO);

    if (argc == 3)
    {
        sscanf(argv[1], "%d", &number_of_prime_to_display);
        sscanf(argv[2], "%lf", &a);
    }
    else
    {
        return 0;
    }

    window = SDL_CreateWindow(
        "Primes on a circle",
        window_position.x,
        window_position.y,
        WINDOW_LENGTH,
        WINDOW_LENGTH,
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    for (int y = 1; y < number_of_prime_to_display; y++)
    {
        if (last_prime != NULL || y == 1) {
            last_prime = draw_n_primes(renderer, center, last_prime, y, y);
        }
    }

    draw_logarithm(renderer, center, a, number_of_prime_to_display);

    SDL_RenderPresent(renderer);

    pause();

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
        }
    }
}