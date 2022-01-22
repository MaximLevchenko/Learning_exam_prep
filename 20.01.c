#include <stdio.h>
#include <stdlib.h>

typedef struct TItem
{
    struct TItem *m_Next;
    int m_Pow;
    int m_Num;
    //TItem () { m_Next = nullptr; m_Pow = 0; m_Num = 0;};
    // TItem (int pow, int num) : m_Pow(pow), m_Num(num), m_Next(nullptr) { };
} TITEM;

TITEM *createItem(int set_num, int set_pow, TITEM *next)
{
    TITEM *n = (TITEM *)malloc(sizeof(*n));
    n->m_Pow = set_pow;
    n->m_Next = next;
    n->m_Num = set_num;
    return n;
}

void insertTail(TITEM **head, int set_num, int set_pow)
{

    TITEM *tmp = NULL;
    // if (head != NULL)
    tmp = *head;
    TITEM *new_element = createItem(set_num, set_pow, NULL);
    if (tmp == NULL)
    {
        tmp = new_element;

        *head = new_element; // * head -> head[0] == *head
        return;
    }
    while (tmp->m_Next != NULL)
    {
        tmp = tmp->m_Next;
    }
    tmp->m_Next = new_element;
    printf("%d %d\n", tmp->m_Next->m_Num, tmp->m_Next->m_Pow);
}

void insertNode(int set_num, int set_pow)
{
}

void freeActualNumbers(char **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(array[i]);
    }
    free(array);
}

void printNodes(TITEM **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        TITEM *temp = array[i];
        while (temp != NULL)
        {
            printf("%d %d  |", temp->m_Num, temp->m_Pow);
            temp = temp->m_Next;
        }
        printf("\n");
    }
}

int findLength(TITEM *array)
{
    TITEM *temp = array;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->m_Next;
    }
    return count;
}

void findSum(TITEM **array, TITEM **third_list)
{
    *third_list = NULL;
    TITEM *tmp1 = array[0];
    TITEM *tmp2 = array[1];

    int length_first = findLength(array[0]);
    int length_second = findLength(array[1]);
    printf("%d %d\n", length_first, length_second);
    insertTail(third_list, 5, 2);
    insertTail(third_list, 7, 3);
    insertTail(third_list, 6, 4);
}

int main(void)
{
    TITEM *a[3];
    // TITEM ** pA = a;

    a[0] = createItem(3, 0,
                      createItem(2, 1,
                                 createItem(9, 3, NULL)));

    a[1] = createItem(7, 0,
                      createItem(4, 2,
                                 createItem(-1, 3, NULL)));

    printNodes(a, 2);
    findSum(a, &a[2]);
    printNodes(a, 3);
}
