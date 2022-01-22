#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct bst_list
{
    int data;
    struct bst_list *p_Left;
    struct bst_list *p_Right;
} BST_list;

// BST_list *p_Root; //pointer to the root

BST_list *createNewNode(int data)
{
    BST_list *new_element = (BST_list *)malloc(sizeof(BST_list));
    new_element->data = data;
    new_element->p_Left = NULL;
    new_element->p_Right = NULL;
    return new_element;
}

BST_list *Insert(BST_list *root, int data)
{
    BST_list *tmp = root;
    if (tmp == NULL)
    {
        tmp = createNewNode(data);
        return tmp;
    }
    else if (data <= tmp->data)
    {
        tmp->p_Left = Insert(tmp->p_Left, data);
    }
    else
    {
        tmp->p_Right = Insert(tmp->p_Right, data);
    }
    return tmp;
}

int Search(BST_list *root, int data_to_search)
{
    if (data_to_search == root->data)
        return 1;
    else if (root == NULL)
        return 0;
    else if (data_to_search <= root->data)
        return Search(root->p_Left, data_to_search);
    else
        return Search(root->p_Right, data_to_search);
}

int deleteNode(BST_list * root,int data_to_delete)
{
    if(data_to_delete == root->data);
}

int main(void)
{
    BST_list *root = NULL;

    root = Insert(root, 20);
    root = Insert(root, 15); // we really don`t have to assign it to root, cause is will not change it anyways
    root = Insert(root, 35); // we really don`t have to assign it to root, cause is will not change it anyways
    root = Insert(root, 50); // we really don`t have to assign it to root, cause is will not change it anyways
    root = Insert(root, 10); // we really don`t have to assign it to root, cause is will not change it anyways
    assert(Search(root, 15) == 1);
    assert(Search(root, 20) == 1);
    assert(Search(root, 35) == 1);
    assert(Search(root, 10) == 1); //this one should fail

    return 0;
}