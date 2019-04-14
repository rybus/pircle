#include "store.h"

void draw_logarithm(SDL_Renderer *renderer, SDL_Point center, double a, int expected_number_of_primes)
{
    int x = 0;
    int y = 0;
    double theta_rad = 0;
    double phi = (1 + sqrt(5)) / 2;
    double b = log(phi) / (M_PI / 2);
    SDL_Color yellow = {255, 255, 0};

    for (theta_rad = 0; x < 15000; theta_rad = theta_rad + M_PI / 180)
    {
        x = a * exp(b * theta_rad * 2) * cos(theta_rad);
        y = a * exp(b * theta_rad * 2) * sin(theta_rad);

        SDL_SetRenderDrawColor(renderer, yellow.r, yellow.g, yellow.b, yellow.a);
        SDL_RenderDrawPoint(renderer, x / 20 + center.x, y / 20 + center.y);
    }
}

int draw_n_primes(SDL_Renderer *renderer, SDL_Point center, int window_length, int expected_number_of_primes)
{
    SDL_Color red = {255, 0, 55};
    double angle;
    double radius;
    int displayed_prime = 0;
    prime* next = NULL;

    llist prime_list = get_n_primes(expected_number_of_primes);

    if (prime_list == NULL)
    {
        printf("not enough primes in the file, %d required", expected_number_of_primes);

        return 1;
    }

    prime *current_prime = prime_list;

    while (displayed_prime < expected_number_of_primes)
    {
        angle = (current_prime->number * 2 * M_PI) / (displayed_prime - 1);
        radius = (displayed_prime*window_length)/expected_number_of_primes;

        draw_point_on_circle(renderer, center, angle, radius, red);

        displayed_prime++;
        if (displayed_prime < expected_number_of_primes)
        {   
            next = current_prime->next;
            free(current_prime);
            current_prime = next;
        }
    }

    return 0;
}

void draw_point_on_circle(SDL_Renderer *renderer, SDL_Point center, double radian, double radius, SDL_Color color)
{
    double x, y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    x = cos(radian) * radius;
    y = sin(radian) * radius;

    SDL_RenderDrawPoint(renderer, x + center.x, y + center.y);
}

void draw_big_point_on_circle(SDL_Renderer *renderer, SDL_Point center, double radian, int radius, SDL_Color color)
{
    double x, y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    x = cos(radian) * radius;
    y = sin(radian) * radius;

    SDL_RenderDrawPoint(renderer, x + center.x, y + center.y);
    SDL_RenderDrawPoint(renderer, x + center.x + 1, y + center.y);
    SDL_RenderDrawPoint(renderer, x + center.x, y + center.y + 1);
    SDL_RenderDrawPoint(renderer, x + center.x - 1, y + center.y);
    SDL_RenderDrawPoint(renderer, x + center.x, y + center.y - 1);
}
