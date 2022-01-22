#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
    int id;
    char *name;
    struct s_list *next;
} t_list;

t_list *create_node(int set_id, char *set_name)
{
    t_list *node = (t_list *)malloc(sizeof(t_list));
    node->id = set_id;
    node->name = set_name;
    node->next = NULL;
    return node;
}

void add_head(t_list **list, int set_id, char *set_name)
{
    t_list *new_element = create_node(set_id, set_name);
    new_element->next = *list; //new_element is now pointing to the head
    *list = new_element;       //we are making new_element a head of the list, so list* is now pointing to new_element
}

void add_tail(t_list **list, int set_id, char *set_name)
{
    t_list *new_element = create_node(set_id, set_name);
    t_list *tmp = *list; //we need temporary pointer to not lose the original pointer to the head
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }                        //we are at the tail
    tmp->next = new_element; //last element is not a pointer to the new_element, new_element becomes tail
}

void insert_node(t_list **list, int set_id, char *set_name, int node_to_insert)
{
    t_list *tmp = *list;      //creating temporary head pointer so we don`t lose original one
    while (tmp != NULL) //iterating through our list
    {
        if (tmp->id == node_to_insert)
        {
            t_list *new_element = create_node(set_id, set_name); //when we found specific one, creating new node
            new_element->next = tmp->next;                       //new_element is now pointing to the element, which was pointed on by the previous node
            tmp->next = new_element;                             //previous node is now pointing to the new_element
        }
        tmp = tmp->next;
    }
}

void delete_node(t_list **list, int node_id_to_delete)//deleting nodes by id`s
{
    int flag = 0;
    t_list *to_delete = *list, *prev = NULL; //making a pointer to the head of the list to save the origin one
    while (to_delete->next != NULL)
    {
        if (flag>1)
            to_delete = to_delete->next;     //iterating through the list
        if (to_delete->id == node_id_to_delete) //when node.next is equal to the id we want to delete
        {
            if (prev == NULL)
            {
                *list = to_delete->next;
                free(to_delete);
                break;
            }
            if (to_delete->next == NULL)
            {
                prev->next = NULL;
                free(to_delete);
                break;
            }
            prev->next = to_delete->next; //previous node is now pointing to the node next to the node we want to delete
            free(to_delete);              //actually deleting the node we want to delete
        }
        prev = to_delete;                //remembering a previous node
        if (!flag)                       //for first time we want to iterate through the list after checking whether its first node or not
            to_delete = to_delete->next; //iterating through the list
        flag++;
    }
}

int main(void)
{
    t_list *list = create_node(5, "nice5");

    add_head(&list, 4, "nice4");
    add_head(&list, 3, "nice3");
    add_head(&list, 2, "nice2");
    add_head(&list, 1, "nice1");

    add_tail(&list, 6, "nice6");
    add_tail(&list, 7, "nice7");
    add_tail(&list, 8, "nice8");
    add_tail(&list, 9, "nice9");

    insert_node(&list, 1000, "INSERT", 2);
    insert_node(&list, 1500, "INSERT", 4);
    insert_node(&list, 7000, "INSERT", 6);
    insert_node(&list, 10590, "INSERT", 1);
    insert_node(&list, 5747, "INSERT", 9);

    // delete_node(&list, 9);
    // delete_node(&list, 2);
    // delete_node(&list, 5);
    // delete_node(&list, 8);
    // delete_node(&list, 7);


    // add_tail(&list, 5747, "INSERT");

    while (list != NULL)
    {
        printf("%d %s\n", list->id, list->name);
        list = list->next;
    }

    return 0;
}