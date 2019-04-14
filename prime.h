#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>

typedef struct prime prime;
struct prime
{
    int number;
    struct prime *next;
};
 
typedef prime* llist;

void draw_point_on_circle(SDL_Renderer *renderer, SDL_Point center, double radian, double radius, SDL_Color color);
int draw_n_primes(SDL_Renderer *renderer, SDL_Point center, int window_length, int expected_number_of_primes);
void draw_logarithm(SDL_Renderer* renderer,  SDL_Point center, double a, int expected_number_of_primes);
void draw_big_point_on_circle(SDL_Renderer *renderer, SDL_Point center, double radian, int radius, SDL_Color color);