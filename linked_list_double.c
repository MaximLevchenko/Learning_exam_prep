#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
    int data;
    char *name;
    struct s_list *p_Next;
    struct s_list *p_Prev;

} t_list;

t_list *head;
t_list *tail;
int node_counter = 0;

t_list *createNode(int set_data, char *set_name)
{
    t_list *node = (t_list *)malloc(sizeof(t_list));
    node->data = set_data;
    node->name = set_name;
    node->p_Next = NULL;
    node->p_Prev = NULL;
    return node;
}

void addHead(int set_data, char *set_name)
{
    t_list *new_element = createNode(set_data, set_name);
    if (head == NULL) //if our list is empty, make it a head
    {
        head = new_element; //if the listed is empty, assigning head and tail to the first node
        tail = new_element;
        node_counter++; //incrementing node counter
        return;
    }
    head->p_Prev = new_element; //making a link between head and node and before it
    new_element->p_Next = head; //making a link between node and previous head
    head = new_element;         //making a new head, cause new_element is now standing before the node
    node_counter++;
}

void addTail(int set_data, char *set_name)
{
    t_list *new_element = createNode(set_data, set_name);
    if (tail == NULL) //if there was no tail defined, we will find one
    {
        head = new_element; //if the listed is empty, assigning head and tail to the first node
        tail = new_element;
        node_counter++;
    }
    new_element->p_Prev = tail; //previous element before adding to the tail is tail
    tail->p_Next = new_element; //making a link between p_Next node of the tail and new_element
    tail = new_element;         //redefining the tail
    node_counter++;
}

void insertNode(int set_data, char *set_name, int node_position)
{
    // int i = 0;
    if (node_counter / 2 > node_position) //if true, then its reasonable to go from head
    {
        t_list *tmp = head;
        t_list *new_element = createNode(set_data, set_name);
        if (node_position == 1)
        {
            new_element->p_Next = head;
            head = new_element;
            node_counter++;
            return;
        }
        for (int j = 0; j < node_position - 2; j++) //coming to the n-1 node
        {
            tmp = tmp->p_Next; //tmp is now on the n-1 node
        }
        new_element->p_Prev = tmp;
        new_element->p_Next = tmp->p_Next;
        tmp->p_Next = new_element;
        node_counter++;
        return;
    }
    // i = node_counter;
    t_list *tmp = tail;
    t_list *new_element = createNode(set_data, set_name);
    for (int i = node_counter; i > node_position - 1; i--) // coming to the node n-1 (counting from the head)
    {
        tmp = tmp->p_Prev;
    }

    new_element->p_Prev = tmp;         //previous pointer is pointing to the n-1 node
    new_element->p_Next = tmp->p_Next; //new node is now pointing to the node of the position we want to insert
    tmp->p_Next = new_element;         //next pointer of n-1 node is now pointing to the new node, making it the 6th node
    node_counter++;
}

void deleteNode(int node_position)
{
    t_list *tmp = head;
    if (node_position == 1)
    {
        head = tmp->p_Next; //moving a head by one node further
        free(tmp);          //deleting the first element
        return;
    }
    for (int i = 0; i < node_position - 2; i++)
    {
        tmp = tmp->p_Next; //tmp points to the n-1`th node
    }
    t_list *tmp2 = tmp->p_Next; //tmp2 points to the n`th node
    tmp->p_Next = tmp2->p_Next; //making a link between n-1`th and n+1`th node
    tmp2->p_Next->p_Prev = tmp->p_Next;
    free(tmp2); // deleting n`th node
}

void print_nodes()
{
    t_list *temp = head;
    while (temp != NULL)
    {
        printf("%d %s\n", temp->data, temp->name);
        temp = temp->p_Next;
    }
}

void print_reverse_nodes()
{
    t_list *temp = tail;
    while (temp != NULL)
    {
        printf("%d %s\n", temp->data, temp->name);
        temp = temp->p_Prev;
    }
}

int main(void)
{

    addHead(7, "nice");
    addHead(6, "nice");
    addHead(5, "nice");
    addTail(15, "Tail");
    addTail(20, "Tail");
    addTail(25, "Tail");
    addTail(67, "Tail");
    addTail(78, "Tail");

    print_nodes();
    printf("------------------------%d\n", node_counter);
    print_reverse_nodes();
    printf("------------------------\n");
    // insertNode(69, "INSERT", 3);
    insertNode(69, "INSERT", 2);
    print_nodes();

    printf("------------------------%d\n", node_counter);

    insertNode(96, "INSERT", 6);
    deleteNode(3);
    print_nodes();

    return 0;
}