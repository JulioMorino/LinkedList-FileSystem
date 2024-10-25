#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "struct_node.h"
#include "fileSystemManagement.c"
#include "fileSystemNavigation.c"
#define MAX_PATH_LENGTH 1024

int main()
{
    int userSelect;
    char confirmation = 'a';
    int answer_validator = 0;
    Node *currentDirectory = initialize_root_directory();

    char name[40] = "";
    int isDirectory = 0;
    int size = 0, errorCode;
    char path[MAX_PATH_LENGTH] = "";
    int pathChanged = 1;
    do
    {
        answer_validator = 0;
        system("cls");
        printf("Sistema de Arquivos com Lista Ligada\n\n");
        if (pathChanged)
        {
            show_current_path(currentDirectory, path);
            pathChanged = 0;
        }
        printf("Caminho atual: %s\n", path);
        printf("Tamanho do diretorio atual: %d", currentDirectory->size);
        printf("\n\nOpcoes: \n\n");
        printf("1 -> Ir para diretorio especifico ...\n");
        printf("2 -> Voltar para diretorio anterior\n");
        printf("-----------------------------------\n");
        printf("3 -> Criar arquivo no diretorio atual\n");
        printf("4 -> Excluir arquivo no diretorio atual\n");
        printf("5 -> Criar pasta no diretorio atual\n");
        printf("6 -> Excluir pasta no diretorio atual\n");
        printf("7 -> Mostrar conteudo do diretorio atual\n");
        printf("0 -> Sair \n:");
        scanf("%d", &userSelect);

        switch (userSelect)
        {
        case 1:
            printf("Insira o caminho completo para onde deseja navegar (exemplo: \\C:\\pasta1\\pasta2): ");
            scanf(" %39[^\n]", &name);
            Node *directoryToNavigate = go_to_another_directory(currentDirectory, name);
            if (directoryToNavigate == NULL)
            {
                show_error(5);
            }
            if (directoryToNavigate != NULL)
            {
                currentDirectory = directoryToNavigate;
                strcpy(path, "");
                pathChanged = 1;
                show_error(0);
            }

            system("pause");
            break;
        case 2:

            break;

        case 3:
            printf("Insira o tamanho do arquivo (bytes): ");
            scanf("%d", &size);
            getchar();
            printf("Insira um nome para o arquivo: ");
            scanf(" %39[^\n]", &name);
            errorCode = create_node_in_current_directory(&currentDirectory, name, size, 0);
            show_error(errorCode);
            system("pause");
            break;

        case 4:
            printf("Insira o nome do arquivo que deseja excluir: ");
            scanf(" %39[^\n]", &name);

            while (!answer_validator)
            {
                printf("Tem certeza que deseja excluir esse arquivo permanentemente?\n[S/N]:  ");
                scanf(" %c", &confirmation);
                getchar(); // getting \n from buffer
                confirmation = toupper(confirmation);

                switch (confirmation)
                {
                case 'S':
                    errorCode = delete_node_in_current_directory(&(currentDirectory->child), name, 0); // 0 is important to indicate that a file is being deleted
                    show_error(errorCode);
                    answer_validator = 1;
                    break;
                case 'N':
                    printf("\nOperacao Cancelada\n");
                    answer_validator = 1;
                    break;
                default:
                    show_error(3);
                    break;
                }
            }

            system("pause");
            break;

        case 5:
            printf("Insira um nome para a nova pasta: ");
            scanf(" %39[^\n]", &name);
            errorCode = create_node_in_current_directory(&currentDirectory, name, 0, 1); // 0: mandatory to initialize folder with 0 bytes size. 1: indicates we are creating a new directory
            show_error(errorCode);
            system("pause");
            break;

        case 6:
            printf("Insira o nome da pasta que deseja excluir: ");
            scanf(" %39[^\n]", &name);

            while (!answer_validator)
            {
                printf("Tudo contido na pasta sera perdido.\nTem certeza que deseja excluir essa pasta permanentemente?\n[S/N]:  ");
                scanf(" %c", &confirmation);
                getchar(); // getting \n from buffer
                confirmation = toupper(confirmation);

                switch (confirmation)
                {
                case 'S':
                    errorCode = delete_node_in_current_directory(&(currentDirectory->child), name, 1); // 0 is important to indicate that a directory is being deleted
                    show_error(errorCode);
                    answer_validator = 1;
                    break;
                case 'N':
                    printf("\nOperacao Cancelada\n");
                    answer_validator = 1;
                    break;
                default:
                    show_error(3);
                    break;
                }
            }
            system("pause");
            break;

        case 7:
            errorCode = show_current_path_content(currentDirectory->child);
            show_error(errorCode);
            system("pause");
            break;
        case 8:
            system("pause");
            break;

        case 9:
            system("pause");
            break;

        case 0:
            break;

        default:
            printf("\n\n Opcao nao valida");
        }
        // getchar(); /* Limpa o buffer de entrada */
    } while ((userSelect != 0));
    system("pause");
}
