#include <stdio.h>
#include <stdlib.h>
#include "struct_node.h"
#include <string.h>

Node *initialize_root_directory();

int create_node_in_current_directory(Node **directoryPointer, char *wishedName, int wishedSize, int isDirectory);
int delete_node_in_current_directory(Node **directoryContent, char *wishedName, int isDirectory);

void verify_repetition_in_directory(Node *directoryPointer, char *wishedName, int isDirectory, int *repetition_detected);
void update_directories_size(Node **directoryPointer, int wishedSize, int increment_or_decrement_indicator);
void show_error(int errorCode);

void show_error(int errorCode)
{
    switch (errorCode)
    {
    case 0:
        printf("\nOperacao feita com sucesso\n");
        break;
    case 1:
        printf("\nDiretorio ainda vazio, operacao nao foi realizada\n");
        break;
    case 2:
        printf("\nNome de arquivo nao encontrado no diretorio atual\n");
        break;
    case 3:
        printf("\nEntrada invalida, tente novamente\n");
        break;
    case 4:
        printf("\nFoi encontrado nome repetido no diretorio. \nRepeticoes sao permitidas apenas entre pastas e arquivos e vice versa.\nContudo, pastas no mesmo diretorio nao podem ter mesmo nome e o mesmo vale para arquivos.\nOperacao cancelada\n");
        break;
    case 5:
        printf("\nCaminho indicado esta incorreto ou nao existe. Verifique se a \\ foi utilizada, por exemplo:\n\\C:\\pasta1exemplo\\pasta2exemplo\n\n");
        break;
    default:
        break;
    }
}
/*
INITIALIZE FILE SYSTEM
*/
Node *initialize_root_directory()
{
    Node *rootDirectory = (Node *)malloc(sizeof(Node));

    strcpy(rootDirectory->name, "C:\\");
    rootDirectory->isDirectory = 1;
    rootDirectory->size = 0;

    rootDirectory->parent = NULL;
    rootDirectory->child = NULL;
    rootDirectory->sibling = NULL;

    return rootDirectory;
}

/*
CREATING NEW NODES
*/

int create_node_in_current_directory(Node **directoryPointer, char *wishedName, int wishedSize, int isDirectory)
{
    int repetition_detected = 0;
    verify_repetition_in_directory(*directoryPointer, wishedName, isDirectory, &repetition_detected);
    if (repetition_detected == 1)
    {
        return 4;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));

    strcpy(new_node->name, wishedName);
    new_node->isDirectory = isDirectory;
    new_node->size = wishedSize;

    new_node->parent = *directoryPointer;
    new_node->child = NULL;
    new_node->sibling = (*directoryPointer)->child;

    (*directoryPointer)->child = new_node;

    // updating the size of all directories by recursion, 1 indicates increment
    update_directories_size(&(*directoryPointer), wishedSize, 1);

    return 0;
}

void verify_repetition_in_directory(Node *directoryPointer, char *wishedName, int isDirectory, int *repetition_detected)
{
    Node *cursor = directoryPointer->child;

    while (cursor != NULL)
    {
        if (strcmp(cursor->name, wishedName) == 0 && cursor->isDirectory == isDirectory)
        {
            (*repetition_detected) = 1;
            break;
        }

        cursor = cursor->sibling;
    }
}

/*
REMOVING NODES
*/
// passar no parametro : currentDirectory->child;
int delete_node_in_current_directory(Node **directoryContent, char *wishedName, int isDirectory)
{

    if (*directoryContent == NULL)
    {
        return 1; // empty directory
    }

    if (strcmp((*directoryContent)->name, wishedName) == 0 && (*directoryContent)->isDirectory == isDirectory)
    {

        Node *nodeParent = (*directoryContent)->parent;
        Node *cursorToDelete = (*directoryContent);
        nodeParent->child = nodeParent->child->sibling;

        // updating the size of all directories by recursion, -1 indicates decrement
        update_directories_size(&nodeParent, cursorToDelete->size, -1);
        free(cursorToDelete);

        return 0;
    }

    Node *current = (*directoryContent)->sibling; // second of the list
    Node *previous = *directoryContent;

    while (current != NULL)
    {
        if (current->isDirectory == isDirectory && strcmp(current->name, wishedName) == 0) // because can have same name, but it is a folder or a file
        {
            break;
        }
        previous = current;
        current = current->sibling;
    }

    if (current == NULL)
    {
        return 2; // file name not found in this directory
    }

    previous->sibling = current->sibling;

    Node *nodeParent = current->parent;
    // updating the size of all directories by recursion, -1 indicates decrement
    update_directories_size(&nodeParent, current->size, -1);

    free(current);

    return 0;
}

/*
UPDATING SIZES AFTER INSERT OR DELETE
*/
void update_directories_size(Node **directoryPointer, int wishedSize, int increment_or_decrement_indicator)
{
    switch (increment_or_decrement_indicator)
    {
    case 1:
        if (*directoryPointer != NULL) // stop condition: when arrived rootDirectory, parent will be NULL
        {
            (*directoryPointer)->size = (*directoryPointer)->size + wishedSize;
            update_directories_size(&((*directoryPointer)->parent), wishedSize, 1);
        }
        break;
    case -1:
        if (*directoryPointer != NULL) // stop condition: when arrived rootDirectory, parent will be NULL
        {
            (*directoryPointer)->size = (*directoryPointer)->size - wishedSize;
            update_directories_size(&((*directoryPointer)->parent), wishedSize, -1);
        }
        break;
    default:
        break;
    }
}