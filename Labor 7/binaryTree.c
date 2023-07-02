#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATASIZE 50

typedef struct node
{
    struct node *left;
    struct node *right;
    int key;
    char data[DATASIZE];
} *node;

node insert(node tree, int newKey, char newData[])
{

    if (tree == NULL)
    {
        node newTree = malloc(sizeof(struct node));
        newTree->key = newKey;
        strncpy(newTree->data, newData, sizeof(newTree->data));
        newTree->left = NULL;
        newTree->right = NULL;

        return newTree;
    }

    if (newKey < tree->key)
    {
        tree->left = insert(tree->left, newKey, newData);
    }
    else if (newKey > tree->key)
    {
        tree->right = insert(tree->right, newKey, newData);
    }
    else
    {
        strncpy(tree->data, newData, sizeof(tree->data));
    }

    return tree;
};

void print_tree(node tree)
{
    if (tree == NULL)
    {
        return;
    }

    print_tree(tree->left);
    printf("Key: %d, Data: %s\n", tree->key, tree->data);
    print_tree(tree->right);
}

int main()
{
    node tree = NULL;
    tree = insert(tree, 25, "Twentyfive");
    tree = insert(tree, 3, "Three");
    tree = insert(tree, 17, "Seventeen");
    tree = insert(tree, 1, "One");
    tree = insert(tree, 3, "Three, The second in its name");
    tree = insert(tree, 89, "Eithy-nine");
    tree = insert(tree, 69, "Sixty-nine");
    tree = insert(tree, 46, "Fourty-six");
    tree = insert(tree, 22, "Twentytwo");
    tree = insert(tree, 89, "Eithy-nine, the second in its name");
    tree = insert(tree, 3, "Three, The third of in its name");

    print_tree(tree);

    return 0;
}