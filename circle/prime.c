#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdint.h>

void pause();
void draw_circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color);
void draw_point_on_circle(SDL_Renderer* renderer, SDL_Point center, double radian, int radius, SDL_Color color);
int check_prime(int a);
void draw_n_primes(SDL_Renderer* renderer,  SDL_Point center, int radius, int number_of_primes, int * existing_primes);
int check_if_divided_by(int a, int multiply);

#define NB_PRIME 1000
static int prime_numbers[NB_PRIME] = {0};

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer* renderer;

    SDL_Point window_position = {         
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    };
    SDL_Point center = {         
        405,
        405
    };

    SDL_Point window_size = {810, 810};   
    SDL_Color blue = {0, 120, 199};
   

    SDL_Init(SDL_INIT_VIDEO);             

    window = SDL_CreateWindow( 
        "Primes on a circle",               
        window_position.x,               
        window_position.y,                
        window_size.x,                   
        window_size.y,                   
        SDL_WINDOW_OPENGL                 
    );

    // Check that the window was successfully made
    if (window == NULL) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    for (int y = 0; y <= NB_PRIME; y++) {       
        draw_n_primes(renderer, center, y, y + 20, prime_numbers);
    
    }

    SDL_RenderPresent(renderer);

    pause();

    // Close and destroy the window
    SDL_DestroyWindow(window); 

    // Clean up
    SDL_Quit();
    return 0; 
}

void draw_n_primes(SDL_Renderer* renderer,  SDL_Point center, int radius, int number_of_primes, int * existing_primes)
{
    double le_point = 0.0;
    SDL_Color red = {255, 66, 55};
    int computed_primes = 0;
    int checked_number = 0;

    while (computed_primes < number_of_primes) {
        le_point = (checked_number*2*M_PI)/number_of_primes;
          
        if (existing_primes[computed_primes] == checked_number) {
            /**SDL_Log("angle %f.2d",  //    Print mouse position
                le_point
            );
                SDL_Log("checked prime number %d",  //    Print mouse position
                checked_number
            );*/
            SDL_Color black_red = {55, 0, 5};
            draw_point_on_circle(renderer, center, le_point, radius, black_red);
            checked_number++;
            computed_primes++;
            continue;
        }

        if (check_prime(checked_number) == 1) {
             printf("drawing prime:  %d (r: %d, angle: %fl)\n", checked_number, radius, le_point);
            SDL_Color red = {255, 0, 55};
            draw_point_on_circle(renderer, center, le_point, radius, red);
            existing_primes[computed_primes] = checked_number;
            computed_primes++;
        }
        checked_number++;
        
    }
     

}

int check_prime(int a)
{
    int c;   
 
   for (c = 2 ; c < a ; c++)
   {
    if (check_if_divided_by(a, c)) {
        return 0;
      }
   }

   if ( c == a ) {
        return 1;
   }      
}


int check_if_divided_by(int a, int multiply)
{
   return (a%multiply == 0);
}

void draw_circle(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	int x, y, m;
	x = 0;
	y = radius;             
	m = 5 - 4*radius;
	while (x <= y)        
    {
        SDL_RenderDrawPoint(renderer, x  + center.x,  y + center.y);
		SDL_RenderDrawPoint(renderer, x  + center.x,  y + center.y);
		SDL_RenderDrawPoint(renderer, y  + center.x,  x + center.y);
		SDL_RenderDrawPoint(renderer, -x + center.x,  y + center.y);
		SDL_RenderDrawPoint(renderer, -y + center.x,  x + center.y);
		SDL_RenderDrawPoint(renderer, x  + center.x, -y + center.y);
		SDL_RenderDrawPoint(renderer, y  + center.x, -x + center.y);
		SDL_RenderDrawPoint(renderer, -x + center.x, -y + center.y);
		SDL_RenderDrawPoint(renderer, -y + center.x, -x + center.y);

		if (m > 0) {
			y = y - 1;
			m = m - 8*y;
		}

		x = x + 1;
		m = m + 8*x + 4;
	}
}

void draw_point_on_circle(SDL_Renderer* renderer, SDL_Point center, double radian, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	double x, y;
	x = cos(radian) * radius;
	y = sin(radian) * radius; 
	
    SDL_RenderDrawPoint(renderer, x/20  + center.x,  y/20 + center.y);
}


void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}