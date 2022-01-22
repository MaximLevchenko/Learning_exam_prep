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

void freeActualNumbers(char **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(array[i]);
    }

    free(array);
}

char *toNumRec(TITEM *x, int *depth)
{
    char *digit = NULL;
    if (x == NULL)
    {
        digit = (char *)malloc(sizeof(char) * *depth + 2);
        memset(digit, '\0', sizeof(char) * *depth + 2);
        return digit;
    }
    (*depth) += 1;
    digit = toNumRec(x->m_Next, depth);
    if (!digit)
    {
        return NULL;
    }
    if (!isdigit(x->m_Digit))
    {
        // if (digit != NULL)
            free(digit);
        return NULL;
    }

    strncat(digit, &(x->m_Digit), 1);
    return digit;
}

// char *toNumRec(TITEM *x, int *depth)
// {
//     char *digit = NULL;
//     char * final_digit = NULL;
//     memset(digit, '\0', sizeof(*digit) * 10);

//     if (!isdigit(x->m_Digit))
//     {
//         return NULL;
//     }
//     if (x->m_Next != NULL)
//     {
//         (*depth++);
//         final_digit = toNumRec(x->m_Next, depth);

//     }
//     if( &(x->m_Digit)==NULL)
//     {
//         digit = (char*)malloc(sizeof(char)* *depth);
//     }
//     strncat(digit, &(x->m_Digit), 1);
//     return digit;
// }

TITEM *maxOf(TITEM **x, int nr)
{
    char **actualNumbers = (char **)malloc(sizeof(*actualNumbers) * nr);

    int depth = 0;
    for (int i = 0; i < nr; i++)
    {
        depth = 0;
        char *number = toNumRec(*(x + i), &depth);
        // printf("%s\n", number);
        if (number == NULL)
        {
            freeActualNumbers(actualNumbers, i);
            return NULL;
        }
        else
        {
            actualNumbers[i] = number;
            // free(number);
        }
    }
    int flag, length;
    int *arr_len = (int *)malloc(sizeof(int) * nr);
    for (int i = 0; i < nr; i++)
    {
        flag = 0, length = 0;
        for (int j = 0; j < strlen(actualNumbers[i]); j++)
        {
            if (actualNumbers[i][j] == '0' && !flag)
            {

                continue;
            }
            flag = 1;
            length++;
        }
        arr_len[i] = strlen(actualNumbers[i]) - length;
        printf("%d ", length);
    }
    printf("without zeros\n");
    for (int i = 0; i < nr; i++)
        printf("%d ", arr_len[i]);
    printf("how many to go forward\n");

    int max = 0, j = 1;
    for (int i = 0; i < nr - 1 && j < nr; j++)
    {
        if ((strlen(actualNumbers[i]) - arr_len[i]) < (strlen(actualNumbers[j]) - arr_len[j]))
        {
            max = j;
            i = max;
            continue;
        }
        else if ((strlen(actualNumbers[i]) - arr_len[i]) == (strlen(actualNumbers[j]) - arr_len[j]))
        {
            if (strcmp(actualNumbers[i] + arr_len[i], actualNumbers[j] + arr_len[j]) > 0)
            {
                max = i;
                continue;
            }
            else if (strcmp(actualNumbers[i] + arr_len[i], actualNumbers[j] + arr_len[j]) < 0)
            {
                max = j;
                i = max;
            }
            else
            {
                max = i;
                continue;
            }
        }
        else
        {
            max = i;
            continue;
        }
    }
    printf("highest is %d\n", max);

    free(arr_len);

    freeActualNumbers(actualNumbers, nr);

    return (x[max]);
}

int main(void)
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

    a[0] = createItem ( '0',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '1', NULL ))));
    a[1] = createItem ( '2',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '1', NULL ))));
    a[2] = createItem ( '1',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '1', NULL))));
    a[3] = createItem ( '2',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '1',
    														   createItem ( '0',
    																		createItem ( '0', NULL ))))));
    assert ( maxOf ( a, 4 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );

    a[0] = createItem ( '1',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '0',
    														   createItem ( '0',
    																		createItem ( '0', NULL ))))));
    a[1] = createItem ( '0',
    					createItem ( '0',
    								 createItem ( '1', NULL )));
    a[2] = createItem ( '1',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '0',
    														   createItem ( '0',
    																		createItem ( '9', NULL ))))));
    a[3] = createItem ( '0',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '0',
    														   createItem ( '0',
    																		createItem ( '0',
    																					 createItem ( '0',
    																								  createItem ( '0',
    																											   createItem ( '0',
    																															createItem ( '0',
    																																		 createItem ( '0',
    																																					  createItem ( '0',
    																																								   createItem ( '0',
    																																												createItem ( '0',
    																																															 createItem ( '0', NULL )))))))))))))));
    assert ( maxOf (a, 4) == a[2] );
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList ( a[2] );
    deleteList ( a[3] );

    a[0] = createItem ( '0',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '0',
    														   createItem ( '0',
    																		createItem ( '0',
    																					 createItem ( '0',
    																								  createItem ( '0',
    																											   createItem ( '0',
    																															createItem ( '0',
    																																		 createItem ( '0',
    																																					  createItem ( '0',
    																																								   createItem ( '0',
    																																												createItem ( '0',
    																																															 createItem ( '0',
    																																																		  createItem ( '0',
    																																																					   createItem ( '0',
    																																																									createItem ( '0',
    																																																												 createItem ( '0',
    																																																															  createItem ( '0',
    																																																																		   createItem ( '0',
    																																																																						createItem ( '1', NULL ))))))))))))))))))))));
    a[1] = createItem ( '1',
    					createItem ( '0',
    								 createItem ( '0',
    											  createItem ( '0',
    														   createItem ( '0',
    																		createItem ( '0',
    																					 createItem ( '0',
    																								  createItem ( '0',
    																											   createItem ( '0',
    																															createItem ( '0',
    																																		 createItem ( '0',
    																																					  createItem ( '0',
    																																								   createItem ( '0',
    																																												createItem ( '0',
    																																															 createItem ( '0',
    																																																		  createItem ( '0',
    																																																					   createItem ( '0',
    																																																									createItem ( '0',
    																																																												 createItem ( '0',
    																																																															  createItem ( '0',
    																																																																		   createItem ( '0',
    																																																																						createItem ( '1', NULL ))))))))))))))))))))));
    assert ( maxOf ( a, 2 ) == a[1] );
    deleteList ( a[0] );
    deleteList ( a[1] );

    a[0] = createItem ( '3',
    					createItem ( '2',
    								 createItem ( '1', NULL )));
    a[1] = createItem ( '6',
    					createItem ( '5',
    								 createItem ( '4', NULL )));
    a[2] = createItem('9',
                      createItem('c',
                                 createItem('b',
                                            createItem('9',
                                                       createItem('9', NULL)))));
    assert(maxOf(a, 3) == NULL);
    deleteList ( a[0] );
    deleteList ( a[1] );
    deleteList(a[2]);

    return 0;
}