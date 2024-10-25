#ifndef STRUCT_NODE
#define STRUCT_NODE

typedef struct node
{
    char name[40];
    int isDirectory;
    int size;

    struct node *parent, *child, *sibling;
} Node;

#endif