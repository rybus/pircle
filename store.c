#include <stdio.h>
#include "store.h"

int generate(int number_of_prime)
{
    int generated_primes = 0;
    int i = 0;

    while (number_of_prime > generated_primes)
    {
        if (is_prime(i)) {
            printf("%d\n", i);
            generated_primes++;
        }
        i++;
    }

    return 0;
}

llist get_n_primes(int number_of_primes)
{
    char buffer[10];
    int read_prime = 1;
    int number_of_read_primes = 0;
    llist prime_list = NULL;

    FILE *fp = fopen("primes.txt", "r");

    if (!feof(fp))
    {
        while (fgets(buffer, 10, fp) != NULL &&  number_of_read_primes <= number_of_primes)
        {
            sscanf(buffer, "%d\n", &read_prime);
            prime_list = add_number_to_list(prime_list, read_prime);
            number_of_read_primes++;
        }
        fclose(fp);
    }

    if(number_of_primes > number_of_read_primes) {
        printf("not enough primes in the file, %d required, %d in the file\n", number_of_primes, number_of_read_primes);

        return NULL;
    }
   
    return prime_list;
}

llist add_number_to_list(llist liste_of_primes, int prime_number)
{
    prime *new_prime = malloc(sizeof(prime));
    new_prime->number = prime_number;
    new_prime->next = NULL;

    if (liste_of_primes == NULL)
    {
        return new_prime;
    }
    else
    {
        prime *temp = liste_of_primes;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_prime;

        return liste_of_primes;
    }

    return new_prime;
}

int is_prime(int number)
{
    int i;

    for (i = 2; i < number; i++)
    {
        if (number % i == 0)
            return 0;
    }

    if (i == number)
        return 1;
}
