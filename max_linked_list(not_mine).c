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

char *toNumberRec(TITEM *x, int *depth)
{
    char *digit = NULL;
    char *lastDigit = NULL;

    if (!isdigit(x->m_Digit))
        return NULL;

    if (x->m_Next!=NULL)
    {
        (*depth)++;
        digit = toNumberRec(x->m_Next, depth);
    }
    else
    {
        lastDigit = (char *)malloc(sizeof(*lastDigit) * *depth + 2);
        memset(lastDigit, '\0', sizeof(*lastDigit) * *depth + 2);
        strncpy(lastDigit, &(x->m_Digit), 1);
        return lastDigit;
    }

    if (digit)
    {
        strncat(digit, &(x->m_Digit), 1);
        return digit;
    }
    else
        return NULL;
}

char *toNumber(TITEM *x)
{
    int depth = 0;
    char *stringNumber = toNumberRec(x, &depth);

    if (!stringNumber)
        return NULL;
    else
        return stringNumber;
}

void freeActualNumbers(char **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(array[i]);
    }

    free(array);
}

TITEM *maxOf(TITEM **x, int nr)
{
    char **actualNumbers = (char **)malloc(sizeof(*actualNumbers) * nr);

    for (int i = 0; i < nr; i++)
    {
        char *number = toNumber(*(x + i));

        if (!number)
        {
            freeActualNumbers(actualNumbers, i);
            return NULL;
        }
        else
        {
            actualNumbers[i] = number;
        }
    }

    int max = 0;
    for (int i = 1; i < nr; i++)
    {
        if (strcmp(actualNumbers[i], actualNumbers[max]) > 0)
            max = i;
    }

    freeActualNumbers(actualNumbers, nr);
    return *(x + max);
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    TITEM *a[5];

    a[0] = createItem('4',
                      createItem('3',
                                 createItem('2',
                                            createItem('1', NULL))));
    a[1] = createItem('2',
                      createItem('3',
                                 createItem('4',
                                            createItem('5', NULL))));
    assert(maxOf(a, 2) == a[1]);
    deleteList(a[0]);
    deleteList(a[1]);

    a[0] = createItem('0',
                      createItem('0',
                                 createItem('0',
                                            createItem('1', NULL))));
    a[1] = createItem('2',
                      createItem('0',
                                 createItem('0',
                                            createItem('1', NULL))));
    a[2] = createItem('1',
                      createItem('0',
                                 createItem('0',
                                            createItem('1', NULL))));
    a[3] = createItem('2',
                      createItem('0',
                                 createItem('0',
                                            createItem('1',
                                                       createItem('0',
                                                                  createItem('0', NULL))))));
    assert(maxOf(a, 4) == a[1]);
    deleteList(a[0]);
    deleteList(a[1]);
    deleteList(a[2]);
    deleteList(a[3]);

    a[0] = createItem('1',
                      createItem('0',
                                 createItem('0',
                                            createItem('0',
                                                       createItem('0',
                                                                  createItem('0', NULL))))));
    a[1] = createItem('0',
                      createItem('0',
                                 createItem('1', NULL)));
    a[2] = createItem('1',
                      createItem('0',
                                 createItem('0',
                                            createItem('0',
                                                       createItem('0',
                                                                  createItem('9', NULL))))));
    a[3] = createItem('0',
                      createItem('0',
                                 createItem('0',
                                            createItem('0',
                                                       createItem('0',
                                                                  createItem('0',
                                                                             createItem('0',
                                                                                        createItem('0',
                                                                                                   createItem('0',
                                                                                                              createItem('0',
                                                                                                                         createItem('0',
                                                                                                                                    createItem('0',
                                                                                                                                               createItem('0',
                                                                                                                                                          createItem('0',
                                                                                                                                                                     createItem('0', NULL)))))))))))))));
    assert(maxOf(a, 4) == a[2]);
    deleteList(a[0]);
    deleteList(a[1]);
    deleteList(a[2]);
    deleteList(a[3]);

    a[0] = createItem('0',
                      createItem('0',
                                 createItem('0',
                                            createItem('0',
                                                       createItem('0',
                                                                  createItem('0',
                                                                             createItem('0',
                                                                                        createItem('0',
                                                                                                   createItem('0',
                                                                                                              createItem('0',
                                                                                                                         createItem('0',
                                                                                                                                    createItem('0',
                                                                                                                                               createItem('0',
                                                                                                                                                          createItem('0',
                                                                                                                                                                     createItem('0',
                                                                                                                                                                                createItem('0',
                                                                                                                                                                                           createItem('0',
                                                                                                                                                                                                      createItem('0',
                                                                                                                                                                                                                 createItem('0',
                                                                                                                                                                                                                            createItem('0',
                                                                                                                                                                                                                                       createItem('0',
                                                                                                                                                                                                                                                  createItem('1', NULL))))))))))))))))))))));
    a[1] = createItem('1',
                      createItem('0',
                                 createItem('0',
                                            createItem('0',
                                                       createItem('0',
                                                                  createItem('0',
                                                                             createItem('0',
                                                                                        createItem('0',
                                                                                                   createItem('0',
                                                                                                              createItem('0',
                                                                                                                         createItem('0',
                                                                                                                                    createItem('0',
                                                                                                                                               createItem('0',
                                                                                                                                                          createItem('0',
                                                                                                                                                                     createItem('0',
                                                                                                                                                                                createItem('0',
                                                                                                                                                                                           createItem('0',
                                                                                                                                                                                                      createItem('0',
                                                                                                                                                                                                                 createItem('0',
                                                                                                                                                                                                                            createItem('0',
                                                                                                                                                                                                                                       createItem('0',
                                                                                                                                                                                                                                                  createItem('1', NULL))))))))))))))))))))));
    assert(maxOf(a, 2) == a[1]);
    deleteList(a[0]);
    deleteList(a[1]);

    a[0] = createItem('3',
                      createItem('2',
                                 createItem('1', NULL)));
    a[1] = createItem('6',
                      createItem('5',
                                 createItem('4', NULL)));
    a[2] = createItem('9',
                      createItem('c',
                                 createItem('b',
                                            createItem('9',
                                                       createItem('9', NULL)))));
    assert(maxOf(a, 3) == NULL);
    deleteList(a[0]);
    deleteList(a[1]);
    deleteList(a[2]);

    return 0;
}
#endif /* __PROGTEST__ */