#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem *m_Next;
    char m_Digit;
} TITEM;

TITEM *createItem(char digit, TITEM *next)
{
    TITEM *n = (TITEM *)malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM *l)
{
    while (l)
    {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}

#endif /* __PROGTEST__ */

int isValid(TITEM *a, TITEM *b)
{
    TITEM *tmp_a = a;
    TITEM *tmp_b = b;

    while (tmp_a != NULL)
    {
        if (!isdigit(tmp_a->m_Digit) || tmp_a->m_Digit - '0' < 0 || tmp_a->m_Digit - '0' > 9)
            return 0;
        tmp_a = tmp_a->m_Next;
    }
    tmp_a = a;
    while (tmp_a->m_Next != NULL)
    {
        tmp_a = tmp_a->m_Next;
    }
    if (tmp_a->m_Digit == '0')
    {
        return 0;
    }

    while (tmp_b != NULL)
    {
        if (!isdigit(tmp_b->m_Digit) || tmp_b->m_Digit - '0' < 0 || tmp_b->m_Digit - '0' > 9)
            return 0;
        tmp_b = tmp_b->m_Next;
    }
    tmp_b = b;
    while (tmp_b->m_Next != NULL)
    {
        tmp_b = tmp_b->m_Next;
    }
    if (tmp_b->m_Digit == '0')
    {
        return 0;
    }
    return 1;
}

int findMaxLength(TITEM *a, TITEM *b)
{
    int cnt_a = 0;
    int cnt_b = 0;
    int max_length;
    while (a != NULL)
    {
        cnt_a++;
        a = a->m_Next;
    }
    while (b != NULL)
    {
        cnt_b++;
        b = b->m_Next;
    }
    if (cnt_a > cnt_b)
        max_length = cnt_a;
    else
        max_length = cnt_b;
    return max_length;
}

TITEM *addList(TITEM *a, TITEM *b)
{
    if (!isValid(a, b))
    {
        return NULL;
    }
    TITEM *tmp_a = a;
    TITEM *tmp_b = b;

    int max_length = findMaxLength(a, b);
    printf("%d\n", max_length);
    TITEM *res = NULL;
    TITEM *tmp_res = res;
    int sum_of_digits = 0;
    int remainder = 0;
    int digit_to_write = 0;

    for (int i = 0; i < max_length + remainder; i++)
    {
        if (tmp_a && tmp_b)
        {
            sum_of_digits = tmp_a->m_Digit - '0' + tmp_b->m_Digit - '0';
        }
        if (tmp_a && !tmp_b)
        {
            sum_of_digits = tmp_a->m_Digit - '0';
        }
        if (!tmp_a && tmp_b)
        {
            sum_of_digits = tmp_b->m_Digit - '0';
        }
        printf("%d ", sum_of_digits);

        if (sum_of_digits > 9)
        {
            TITEM *new_element = malloc(sizeof(*new_element));
            new_element->m_Digit = (sum_of_digits + remainder - 10) + '0';
            new_element->m_Next = NULL;
            if (tmp_res == NULL)
            {
                tmp_res = new_element;
                res = tmp_res;
            }
            else
            {
                tmp_res->m_Next = new_element;
                tmp_res = new_element;
            }
            remainder = 1;
        }
        else
        {
            TITEM *new_element = malloc(sizeof(*new_element));
            new_element->m_Digit = (sum_of_digits + remainder) + '0';
            new_element->m_Next = NULL;
            if (tmp_res == NULL)
            {
                tmp_res = new_element;
                res = tmp_res;
            }
            else
            {
                tmp_res->m_Next = new_element;
                tmp_res = new_element;
            }
            remainder = 0;
        }

        if (tmp_a)
            tmp_a = tmp_a->m_Next;
        if (tmp_b)
            tmp_b = tmp_b->m_Next;
    }

    return res;
}

/* DIY */

#ifndef __PROGTEST__

int main(int argc, char *argv[])
{
    TITEM *a, *b, *res;

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('7', createItem('4',
                                   createItem('5', NULL)));
    res = addList(a, b);
    assert(res->m_Digit == '0');
    assert(res->m_Next->m_Digit == '9');
    assert(res->m_Next->m_Next->m_Digit == '0');
    assert(res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert(res->m_Next->m_Next->m_Next->m_Next == NULL);

    deleteList(res);
    deleteList(a);
    deleteList(b);
    return 0;
}

#endif /* __PROGTEST__ */