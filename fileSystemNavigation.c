#include <stdio.h>
#include <stdlib.h>
#include "struct_node.h"
#include <string.h>
#define MAX_PATH_LENGTH 1024

int show_current_path(Node *currentDirectory, char *path);
int show_current_path_content(Node *directoryContent);
Node *go_to_another_directory(Node *directoryPointer, char *wishedPath);

/*
INFO ABOUT CURRENT PATH
*/
int show_current_path(Node *currentDirectory, char *path)
{
    char temp[MAX_PATH_LENGTH] = "";

    if (currentDirectory != NULL)
    {
        strcpy(temp, currentDirectory->name);
        strcat(temp, path);
        strcpy(path, temp);
        show_current_path(currentDirectory->parent, path);
    }

    return 0;
}

int show_current_path_content(Node *directoryContent)
{
    // passar no parametro : currentDirectory->child;
    if (directoryContent != NULL)
    {
        if (directoryContent->isDirectory)
        { // if this node is a folder, that is, isDirectory marked as true
            printf("\nPasta: ");
        }
        else
        {
            printf("\nArquivo: ");
        }

        printf("%s\nTamanho: %d bytes\t\t||\n", directoryContent->name, directoryContent->size);
        printf("==========================\n");

        show_current_path_content(directoryContent->sibling);
    }

    return 0;
}

/*
CHANGING DIRECTORIES
*/
Node *go_to_another_directory(Node *directoryPointer, char *wishedPath)
{

    if (wishedPath == NULL || wishedPath[0] != '\\')
    {
        return NULL;
    }

    // going back to the root
    while (directoryPointer->parent != NULL)
    {
        directoryPointer = directoryPointer->parent;
    }

    if (strcmp(wishedPath, "\\C:") == 0)
    {
        return directoryPointer; // user wants to go back to root
    }

    wishedPath += 3; // skipping C: from search
    // example "\C:\folder1\folder2" will be now: "\folder1\folder2"

    char *token = strtok(wishedPath, "\\");

    while (token != NULL)
    {
        Node *directoryContent = directoryPointer->child;
        int found = 0;

        // comparison between the name we found and the current token
        while (directoryContent != NULL)
        {
            if (strcmp(directoryContent->name, token) == 0 && directoryContent->isDirectory)
            {
                // moving to this directory
                directoryPointer = directoryContent;
                found = 1;
                break;
            }
            directoryContent = directoryContent->sibling;
        }

        if (!found)
        {
            return NULL;
        }

        // next token, which is, next name in wishedPath, but without bar, that is separating directories names
        token = strtok(NULL, "\\");
    }

    return directoryPointer;
}