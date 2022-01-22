#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char name[101];
    int count_similar;
} words;

int inArray(char *buffer, words *products, int number_products, int *index_found)
{
    if (number_products == 0)
        return 0;
    for (int i = 0; i < number_products; i++)
    {
        if (strcmp(buffer, products[i].name) == 0)
        {
            *index_found = i;
            return 1;
        }
    }
    return 0;
}

int compare(const void *a, const void *b) // code from stackoverflow https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs
{
    words *orderA = (words *)a;
    words *orderB = (words *)b;
    return (orderB->count_similar - orderA->count_similar);
}

void printMax(words *products, int number_products)
{
    if (number_products < 10)
    {
        for (int i = 0; i < number_products; i++)
        {
            printf("%s %dx\n", products[i].name, products[i].count_similar);
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            printf("%s %dx\n", products[i].name, products[i].count_similar);
        }
    }
}

int isValid(char *buffer)
{
    int length = strlen(buffer);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(buffer[i]))
            return 0;
    }
    return 1;
}

int main(void)
{
    words *products = (words *)malloc(sizeof(*products) * 100);
    char *buffer = NULL;
    int read = 0, realloc_variable = 10, memory_counter = 0, number_products = 0, index_found;
    while (!feof(stdin))
    {
        buffer = (char *)malloc(sizeof(char *) * 100);
        memset(buffer, '\0', sizeof(char *) * 100);
        while ((read = scanf(" %s", buffer)) != feof(stdin) && isValid(buffer))
        {

            if (read != 0 && feof(stdin))
            {
                qsort(products, number_products, sizeof(words), compare);
                printMax(products, number_products);
                free(products);
                free(buffer);
                return 1;
            }
            if (++memory_counter > realloc_variable / 2)
            {
                realloc_variable += (realloc_variable > 100) ? realloc_variable * 1 / 2 : 10;
                products = (words *)realloc(products, realloc_variable * sizeof(*products));
            }
            if (inArray(buffer, products, number_products, &index_found))
            {
                products[index_found].count_similar++;
                if (buffer != NULL)
                {
                    free(buffer);
                    buffer = NULL;
                }
                break;
            }

            products[number_products].count_similar = 1;
            strcpy(products[number_products].name, buffer);
            free(buffer);
            buffer = NULL;
            number_products++;
            break;
        }
        if (buffer != NULL)
        {
            printf("Nespravny vstup\n");
            free(buffer);
            free(products);
            return 0;
        }
    }
    return 0;
}