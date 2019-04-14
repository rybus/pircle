#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "store.h"

void pause();
int display(int number_of_primes, double expension_factor);

#define WINDOW_LENGTH 1000

int main(int argc, char *argv[])
{
    char *param_generate = "generate";
    double expension_factor;
    int number_of_primes = 0;

    if (argc == 3)
    {
        if (strcmp(argv[1], param_generate) == 0)
        {
            sscanf(argv[2], "%d", &number_of_primes);
            return generate(number_of_primes);
        }
        else
        {
            sscanf(argv[1], "%d", &number_of_primes);
            sscanf(argv[2], "%lf", &expension_factor);

            return display(number_of_primes, expension_factor);
        }
    }

    printf("no enough argument provided\n");

    return 0;
}

int display(int number_of_primes, double expension_factor)
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Point window_position = {
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED};
    SDL_Point center = {
        WINDOW_LENGTH / 2,
        WINDOW_LENGTH / 2};

    SDL_Point window_size = {WINDOW_LENGTH, WINDOW_LENGTH};

    SDL_Init(SDL_INIT_VIDEO);
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

    draw_n_primes(renderer, center, WINDOW_LENGTH, number_of_primes);

    //draw_logarithm(renderer, center, expension_factor, number_of_primes);

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