#include "store.h"

void draw_logarithm(SDL_Renderer *renderer, SDL_Point center, double a, int expected_number_of_primes)
{
    int x = 0;
    int y = 0;
    int theta = 0;
    double theta_rad = 0;
    double phi = (1 + sqrt(5)) / 2;
    double b = log(phi) / (M_PI / 2);

    for (theta = 0; x < 1000; theta++)
    {
        theta_rad = (theta * M_PI) / 180;
        x = a * exp(b * theta_rad / 2) * cos(theta_rad);
        y = a * exp(b * theta_rad / 2) * sin(theta_rad);

        SDL_Color blue = {255, 255, 0};
        SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
        SDL_RenderDrawPoint(renderer, x + center.x, y + center.y);
    }
}

prime *draw_n_primes(SDL_Renderer *renderer, SDL_Point center, prime *last_prime, int radius, int expected_number_of_primes)
{
    double angle;
    SDL_Color black_red = {55, 0, 55};
    SDL_Color red = {255, 0, 55};
    int checked_number = 0;
    int displayed_prime = 0;

    llist prime_list = get_n_primes(expected_number_of_primes);

    if (prime_list == NULL)
    {
        printf("not enough primes in files, %d required", expected_number_of_primes);

        return NULL;
    }

    prime *current_prime = prime_list;

    while (displayed_prime < expected_number_of_primes)
    {
        angle = (checked_number * 2 * M_PI) / expected_number_of_primes;

        if (checked_number == current_prime->number)
        {
            if (checked_number > last_prime->number || last_prime->number == -1)
            {
                draw_point_on_circle(renderer, center, angle, radius, red);
            }

            displayed_prime++;
            if (displayed_prime < expected_number_of_primes)
            {
                current_prime = current_prime->next;
            }
        }

        checked_number++;
    }

    return current_prime;
}

void draw_point_on_circle(SDL_Renderer *renderer, SDL_Point center, double radian, int radius, SDL_Color color)
{
    double x, y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    x = cos(radian) * radius;
    y = sin(radian) * radius;

    SDL_RenderDrawPoint(renderer, x / 5 + center.x, y / 5 + center.y);
}
