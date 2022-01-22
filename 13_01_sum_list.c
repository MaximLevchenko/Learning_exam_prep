#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

typedef struct s_list
{
    char digit;
    struct s_list *p_Next;
} t_list;
t_list *createItem(char digit, t_list *next)
{
    t_list *n = (t_list *)malloc(sizeof(*n));
    n->digit = digit;
    n->p_Next = next;
    return n;
}
// t_list *head = NULL;

// t_list *createNode(char set_digit)
// {
//     t_list *new_element = (t_list *)malloc(sizeof(t_list));
//     new_element->digit = set_digit;
//     new_element->p_Next = NULL;
//     return new_element;
// }

// void addTail(char set_digit)
// {
//     t_list *new_element = createNode(set_digit);
//     t_list *tmp = head;
//     if (head == NULL)
//     {
//         head = new_element;
//         return;
//     }
//     while (tmp->p_Next != NULL)
//     {
//         tmp = tmp->p_Next;
//     }
//     tmp->p_Next = new_element;
// }
void freeList(char **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(array[i]);
    }

    free(array);
}
void printNodes(t_list *head)
{
    t_list *tmp = head;
    while (tmp != NULL)
    {
        printf("%c", tmp->digit);
        tmp = tmp->p_Next;
    }
    printf("\n");
}

char *findSum(char **number_array)
{
    int min_length, min_el, max_el;
    if (strlen(number_array[0]) > strlen(number_array[1]))
    {
        min_length = strlen(number_array[1]);
        min_el = 1;
        max_el = 0;
    }
    else if (strlen(number_array[0]) < strlen(number_array[1]))
    {
        min_length = strlen(number_array[0]);
        min_el = 1;
        max_el = 0;
    }
    else
    {
        min_length = strlen(number_array[1]); //or [1] doesn`t matter
        min_el = max_el = 1;
    }
    number_array[2] = (char *)malloc(sizeof(char) * strlen(number_array[max_el]));
    int flag = 0, digit = 0, flag_new_array;
    char digit_to_write;
    for (int i = min_length - 1; i >= 0; i--)
    {
        if (flag)
        {
            digit = (number_array[0][i] - '0') + (number_array[1][i] - '0') + 1;
            if (digit > 9)
            {
                if (i == 0)
                {
                    flag_new_array = 1;
                }
                digit_to_write = digit % 10 + '0';
                number_array[2][i] = digit_to_write;
                flag = 1;
            }
            else
            {
                digit_to_write = digit + '0';
                number_array[2][i] = digit_to_write;
                printf("%c\n", digit_to_write);
                flag = 0;
            }
        }
        else
        {
            digit = (number_array[0][i] - '0') + (number_array[1][i] - '0');
            if (digit > 9)
            {
                if (i == 0)
                {
                    flag_new_array = 1;
                }
                digit_to_write = digit % 10 + '0';
                printf("%c\n", digit_to_write);
                number_array[2][i] = digit_to_write;
                flag = 1;
            }
            else
            {
                digit_to_write = digit + '0';
                printf("%c\n", digit_to_write);
                number_array[2][i] = digit_to_write;
            }
        }
    }
    for (int i = min_length; i < strlen(number_array[max_el]); i++)
    {
        number_array[2][i] = number_array[max_el][i];
    }
    char *new_bigger_array = NULL;
    if (flag_new_array)
    {
        new_bigger_array = (char *)malloc(sizeof(char) * strlen(number_array[2]) + 3);
        memset(new_bigger_array, '\0', sizeof(char) * strlen(number_array[2]) + 3);
        for (int i = 1, j = 0; i < strlen(number_array[max_el]) + 1; i++, j++)
        {
            new_bigger_array[i] = number_array[2][j];
        }
        new_bigger_array[0] = '1';
        memset(number_array, '\0', sizeof(char) * strlen(number_array[2]) + 3);
        strncpy(number_array[2], new_bigger_array, strlen(new_bigger_array));
    }
    printf("%s\n", number_array[2]);
    return number_array[2];
}

char *toNumRec(t_list *x, int *depth) // t_list *x cause we are accepting only one linked list
{
    char *str = NULL;
    char *last_digit = NULL;
    if (x->p_Next == NULL)
    {
        if (x->digit == '0')
        {
            if (str != NULL)
            {
                free(str);
            }
            return NULL;
        }
        str = (char *)malloc(sizeof(char) * *depth + 5);
        memset(str, '\0', sizeof(char) * *depth + 5);
        last_digit = (char *)malloc(sizeof(char)); //we need this one to remember last digit of the tree
        memset(last_digit, '\0', sizeof(char));
        strncpy(last_digit, &(x->digit), 1);
        return last_digit;
    }
    (*depth)++;
    str = toNumRec(x->p_Next, depth);
    if (!str)
    {
        return NULL;
    }
    if (!isdigit(x->digit))
    {
        free(str);
        return NULL;
    }

    strncat(str, &(x->digit), 1);
    return str;
}
char *sumOf(t_list **x) // t_list ** x cause we are accepting array of linked lists
{
    int el_count = 2;
    int depth = 0;

    char **number_array = (char **)malloc(sizeof(char *) * el_count + 2);
    for (int i = 0; i < el_count; i++)
    {
        depth = 0;
        char *number = toNumRec((x[i]), &depth);
        printf("%s", number);
        printf("\n");
        if (number == NULL)
        {
            freeList(number_array, i);
        }
        number_array[i] = number;
    }
    return findSum(number_array);
}

int main(void)
{

    t_list *a[5]; //array of linked lists

    a[0] = createItem('3',
                   createItem('4',
                              createItem('9', NULL)));
    a[1] = createItem('0',
                   createItem('9', NULL));

    sumOf(a);
    // printNodes();
    return 0;
}