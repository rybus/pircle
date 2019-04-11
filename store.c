#include <stdio.h>
#include "store.h"

void store(int prime)
{
    char buffer[8];
    FILE *fp = fopen("primes.txt", "a");
    fprintf(fp, "%d\n", prime);
    fclose(fp);
}

llist get_n_primes(int number_of_primes)
{
    char buffer[8];
    int read_prime = 1;
    int number_of_read_primes = 1;
    llist prime_list = NULL;

    FILE *fp = fopen("primes.txt", "r");

    if (!feof(fp))
    {
        while (fgets(buffer, 8, fp) != NULL && number_of_primes >= number_of_read_primes)
        {
            sscanf(buffer, "%d\n", &read_prime);
            prime_list = add_number_to_list(prime_list, read_prime);
            number_of_read_primes++;
        }
        fclose(fp);
    }

    while (number_of_primes >= number_of_read_primes)
    {
        read_prime = get_next_prime(read_prime);
        store(read_prime);
        prime_list = add_number_to_list(prime_list, read_prime);
        number_of_read_primes++;
    }
    return prime_list;
}

int get_next_prime(int prime)
{
    prime++;
    while (is_prime(prime) != 1)
    {
        prime++;
    }

    return prime;
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
