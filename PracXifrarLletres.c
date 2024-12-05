#include <stdio.h>
#include <stdlib.h>
#define MAX 80

void construir_matriu_xifrat(char matriu_x[7][7], int clau)
{
    matriu_x[0][0]='0', matriu_x[0][1]='X', matriu_x[0][2]='I', matriu_x[0][3]='F', matriu_x[0][4]='R', matriu_x[0][5]='A', matriu_x[0][6]='T';
    matriu_x[1][0]='N', matriu_x[2][0]='O', matriu_x[3][0]='R', matriu_x[4][0]='M', matriu_x[5][0]='A', matriu_x[6][0]='L';

    char matriu_clau[6][6] =
    {
        {'A', 'B', 'C', 'D', 'E', 'F'},
        {'G', 'H', 'I', 'J', 'K', 'L'},
        {'M', 'N', 'O', 'P', 'Q', 'R'},
        {'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', ' ', '1', '2', '3'},
        {'4', '5', '6', '7', '8', '9'}
    };

    int fila, col, f, c, k;

    k = 1;

    if (clau == 0)
    {
        fila = 0;
        col = 0;
    }
    else
    {
        for (fila = 0; fila < 6 && k <= clau; fila++)
        {
            for (col = 0; col < 6 && k <= clau; col++)
            {
                k++;
            }
        }

        fila = fila - 1;
    }

    for (f = 1; f < 7; f++)
    {
        for (c = 1; c < 7; c++)
        {
            matriu_x[f][c] = matriu_clau[fila][col];
            if (fila == 5 && col == 5)
            {
                fila = 0;
                col = 0;
            }
            else if (col == 5)
            {
                fila++;
                col = 0;
            }
            else
                col++;
        }
    }
}

void xifrar_frase(char frase[], char matriu_x[][7], char frase_xifrada[])
{
    int i, j, w, z;

    for (i = 0; i < MAX; i++)
    {
        if ((frase[i] >= 'a') && (frase[i] <= 'z'))
        {
            frase[i] = frase[i] - 32; /* Convertimos minúsculas a mayúsculas en ASCII */
        }
    }

    i = 0;
    j = 0;

    while (frase[i] != '\n')
    {
        for (w = 1; w < 7; w++)
        {
            for (z = 1; z < 7; z++)
            {
                if (matriu_x[w][z] == frase[i])
                {
                    frase_xifrada[j] = matriu_x[w][0];
                    frase_xifrada[j + 1] = matriu_x[0][z];
                }
            }
        }
        i++;
        j = j + 2;
    }
    frase_xifrada[j] = '\0';
}

void desxifrar_frase(char frase[], char matriu_x[][7], char frase_desxifrada[])
{
    int i, j, w, z;

    for (i = 0; i < MAX; i++)
    {
        if ((frase[i] >= 'a') && (frase[i] <= 'z'))
        {
            frase[i] = frase[i] - 32;
        }
    }

    i = 0;
    j = 0;

    while (frase[i] != '\n')
    {
        for (w = 0; w < 7; w++)
        {
            for (z = 0; z < 7; z++)
            {
                if (matriu_x[w][0] == frase[i])
                {
                    if (matriu_x[0][z] == frase[i + 1])
                    {
                        frase_desxifrada[j] = matriu_x[w][z];
                    }
                }
            }
        }
        i = i + 2;
        j++;
    }
    frase_desxifrada[j] = '\0';
}

void mostrar_menu()
{
    printf("\nTria una opcio\n\n");
    printf("[1] Encriptar un text introduit pel teclat\n");
    printf("[2] Desencriptar un text introduit pel teclat\n");
    printf("[3] Encriptar un text inclos en un arxiu de text, Nom del arxiu: Text_a_xifrar\n");
    printf("[4] Desencriptar un text inclos en un arxiu de text, Nom del arxiu: Text_a_desxifrar\n");
    printf("[5] Tancar programa\n");
}

int main()
{
    int opc, n;
    char matriu_xifrat[7][7];
    char text[MAX];
    char text_xifrat[MAX * 2];
    char text_desxifrat[MAX];
    FILE *fit;
    FILE *fit_x;

    printf("Introdueix una clau\n");
    scanf("%d", &n);

    if (n <= 35)
    {
        construir_matriu_xifrat(matriu_xifrat, n);

        do
        {
            mostrar_menu();
            scanf("%d", &opc);

            switch (opc)
            {
            case 1:
                printf("\nIntrodueix la frase\n");
                fflush(stdin);
                fgets(text, MAX, stdin);
                xifrar_frase(text, matriu_xifrat, text_xifrat);
                printf("\nText xifrat: %s\n", text_xifrat);
                break;

            case 2:
                printf("\nIntrodueix la frase\n");
                fflush(stdin);
                fgets(text, MAX * 2, stdin);
                desxifrar_frase(text, matriu_xifrat, text_desxifrat);
                printf("\nText desxifrat: %s\n", text_desxifrat);
                break;

            case 3:
                fit = fopen("Text_a_xifrar.txt", "r");
                fit_x = fopen("text_xifrat.txt", "w");

                if (fit == NULL)
                {
                    printf("Error en obrir el fitxer\n");
                }
                else
                {
                    while (fgets(text, MAX, fit) != NULL)
                    {
                        xifrar_frase(text, matriu_xifrat, text_xifrat);
                        fprintf(fit_x, "%s\n", text_xifrat);
                    }
                }
                fclose(fit);
                fclose(fit_x);
                break;

            case 4:
                fit = fopen("Text_a_desxifrar.txt", "r");
                fit_x = fopen("text_desxifrat.txt", "w");

                if (fit == NULL)
                {
                    printf("Error en obrir el fitxer\n");
                }
                else
                {
                    while (fgets(text, MAX * 2, fit) != NULL)
                    {
                        desxifrar_frase(text, matriu_xifrat, text_desxifrat);
                        fprintf(fit_x, "%s\n", text_desxifrat);
                    }
                }
                fclose(fit);
                fclose(fit_x);
                break;

            case 5:
                printf("S'ha tancat el programa\n");
                break;

            default:
                printf("Opcio no valida, torna a intentar-ho.\n");
                break;
            }
        } while (opc != 5);
    }
    else
    {
        printf("Introdueix un numero dins del rang\n");
    }

    return 0;
}
