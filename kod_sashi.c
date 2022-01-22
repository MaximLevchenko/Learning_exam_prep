#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TList
{
    char t_Digit;
    struct TList *t_Next;
} TLIST;

TLIST *createDefNode(char set_digit, TLIST *set_next)
{
    TLIST *new_node = (TLIST *)malloc(sizeof(*new_node));
    new_node->t_Digit = set_digit;
    new_node->t_Next = set_next;

    return new_node;
}

void deleteList(TLIST *head)
{
    while (head)
    {
        TLIST *tmp = head->t_Next;
        free(head);
        head = tmp;
    }
}

TLIST *createNode(char set_digit)
{
    TLIST *new_node = (TLIST *)malloc(sizeof(*new_node));
    new_node->t_Digit = set_digit;
    new_node->t_Next = NULL;

    return new_node;
}

void appendNode(char set_digit, TLIST **list)
{
    TLIST *new_node = createNode(set_digit);
    TLIST *tmp = *list;
    while (tmp->t_Next)
        tmp = tmp->t_Next;
    tmp->t_Next = new_node;
}

TLIST *sumOf(TLIST **list)
{
    TLIST *sum_list = NULL;
    int flag = 0;

    if (*list && *(list + 1))
    {
        TLIST *tmp_list = *list, *tmp_sum = sum_list;
        while (tmp_list)
        {
            if (!isdigit(tmp_list->t_Digit) || (!tmp_list->t_Next && tmp_list->t_Digit == '0'))
            {
                deleteList(sum_list);
                sum_list = NULL;
                return sum_list;
            }
            if (sum_list)
                appendNode(tmp_list->t_Digit, &sum_list);
            else
                tmp_sum = createNode(tmp_list->t_Digit);
            tmp_list = tmp_list->t_Next;
            tmp_sum = tmp_sum->t_Next;
        }

        tmp_list = *(list + 1), tmp_sum = sum_list;
        while (tmp_sum)
        {
            if (tmp_list)
            {
                if (!isdigit(tmp_list->t_Digit) || (!tmp_list->t_Next && tmp_list->t_Digit == '0'))
                {
                    deleteList(sum_list);
                    sum_list = NULL;
                    return sum_list;
                }
                int int_Digit = (tmp_list->t_Digit - '0' + tmp_sum->t_Digit - '0');
                if (flag == 1)
                {
                    int_Digit++;
                    flag = 0;
                }
                if (int_Digit >= 10)
                    flag = 1;
                char res_Digit = (int_Digit % 10) + '0';
                tmp_sum->t_Digit = res_Digit;
                if (!tmp_sum->t_Next && tmp_list->t_Next)
                    appendNode('0', &sum_list);
                if (!tmp_sum->t_Next && !tmp_list->t_Next && flag == 1)
                    appendNode('1', &sum_list);
                tmp_list = tmp_list->t_Next;
            }
            else
            {
                int int_Digit = (tmp_sum->t_Digit - '0') + flag;
                flag = 0;
                if (int_Digit >= 10)
                    flag = 1;
                char res_Digit = (int_Digit % 10) + '0';
                tmp_sum->t_Digit = res_Digit;
            }
            tmp_sum = tmp_sum->t_Next;
        }
    }
    while (sum_list)
    {
        printf("%c\n", sum_list->t_Digit);
        sum_list = sum_list->t_Next;
    }

    return sum_list;
}

int main(int argc, char *argv[])
{
    TLIST *a[2];

    a[0] = createDefNode('4',
                         createDefNode('3',
                                       createDefNode('2',
                                                     createDefNode('1', NULL))));
    a[1] = createDefNode('2',
                         createDefNode('3',
                                       createDefNode('4',
                                                     createDefNode('5', NULL))));

    // assert(sumOf(a, 2) == a[1]);
    sumOf(a);
    deleteList(a[0]);
    deleteList(a[1]);

    // a[0] = createItem('0',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('1', NULL))));
    // a[1] = createItem('2',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('1', NULL))));
    // a[2] = createItem('1',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('1', NULL))));
    // a[3] = createItem('2',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('1',
    // 																	createItem('0',
    // 																				  createItem('0', NULL))))));

    // assert(maxOf(a, 4) == a[1]);
    // deleteList(a[0]);
    // deleteList(a[1]);
    // deleteList(a[2]);
    // deleteList(a[3]);

    // a[0] = createItem('1',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('0',
    // 																	createItem('0',
    // 																				  createItem('0', NULL))))));
    // a[1] = createItem('0',
    // 						createItem('0',
    // 									  createItem('1', NULL)));
    // a[2] = createItem('1',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('0',
    // 																	createItem('0',
    // 																				  createItem('9', NULL))))));
    // a[3] = createItem('0',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('0',
    // 																	createItem('0',
    // 																				  createItem('0',
    // 																								 createItem('0',
    // 																												createItem('0',
    // 																															  createItem('0',
    // 																																			 createItem('0',
    // 																																							createItem('0',
    // 																																										  createItem('0',
    // 																																														 createItem('0',
    // 																																																		createItem('0',
    // 																																																					  createItem('0', NULL)))))))))))))));
    // assert(maxOf(a, 4) == a[2]);
    // deleteList(a[0]);
    // deleteList(a[1]);
    // deleteList(a[2]);
    // deleteList(a[3]);

    // a[0] = createItem('0',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('0',
    // 																	createItem('0',
    // 																				  createItem('0',
    // 																								 createItem('0',
    // 																												createItem('0',
    // 																															  createItem('0',
    // 																																			 createItem('0',
    // 																																							createItem('0',
    // 																																										  createItem('0',
    // 																																														 createItem('0',
    // 																																																		createItem('0',
    // 																																																					  createItem('0',
    // 																																																									 createItem('0',
    // 																																																													createItem('0',
    // 																																																																  createItem('0',
    // 																																																																				 createItem('0',
    // 																																																																								createItem('0',
    // 																																																																											  createItem('0',
    // 																																																																															 createItem('1', NULL))))))))))))))))))))));
    // a[1] = createItem('1',
    // 						createItem('0',
    // 									  createItem('0',
    // 													 createItem('0',
    // 																	createItem('0',
    // 																				  createItem('0',
    // 																								 createItem('0',
    // 																												createItem('0',
    // 																															  createItem('0',
    // 																																			 createItem('0',
    // 																																							createItem('0',
    // 																																										  createItem('0',
    // 																																														 createItem('0',
    // 																																																		createItem('0',
    // 																																																					  createItem('0',
    // 																																																									 createItem('0',
    // 																																																													createItem('0',
    // 																																																																  createItem('0',
    // 																																																																				 createItem('0',
    // 																																																																								createItem('0',
    // 																																																																											  createItem('0',
    // 																																																																															 createItem('1', NULL))))))))))))))))))))));
    // assert(maxOf(a, 2) == a[1]);
    // deleteList(a[0]);
    // deleteList(a[1]);

    // a[0] = createItem('3',
    // 						createItem('2',
    // 									  createItem('1', NULL)));
    // a[1] = createItem('6',
    // 						createItem('5',
    // 									  createItem('4', NULL)));
    // a[2] = createItem('9',
    // 						createItem('c',
    // 									  createItem('b',
    // 													 createItem('9',
    // 																	createItem('9', NULL)))));
    // assert(maxOf(a, 3) == NULL);
    // deleteList(a[0]);
    // deleteList(a[1]);
    // deleteList(a[2]);

    return 0;
}
