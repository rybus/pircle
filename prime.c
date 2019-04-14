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

prime *draw_n_primes(SDL_Renderer *renderer, SDL_Point center, prime *last_prime, int radius, int expected_number_of_primes)
{
    double angle;
    SDL_Color grey = {100, 100, 100};
    SDL_Color red = {255, 0, 55};
    SDL_Color green = {0, 255, 0};
    SDL_Color blue = {0, 0, 255};
    int checked_number = 0;
    int displayed_prime = 0;
    int number_a_displayed = 0;
    int number_b_displayed = 0;
    int number_c_displayed = 0;

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
            if (checked_number == last_prime->number)
            {
                draw_point_on_circle(renderer, center, angle, radius, grey);
            }
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

        if (checked_number == 277 && number_a_displayed == 0)
        {
            draw_big_point_on_circle(renderer, center, angle, radius, green);
            number_a_displayed = 1;
        }

        if (checked_number == 13 && number_b_displayed == 0)
        {
            draw_big_point_on_circle(renderer, center, angle, radius, green);
            number_b_displayed = 1;
        }

        if (checked_number == 3601 && number_c_displayed == 0)
        {
            draw_big_point_on_circle(renderer, center, angle, radius, blue);
            number_c_displayed = 1;
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
