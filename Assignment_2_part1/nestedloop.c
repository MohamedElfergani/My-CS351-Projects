/* PART 1 C LANG */
#include <stdio.h>

int main()
{
    int i;
    int space;
    int rows = 8; 
    int symbols = 0;

    for (i = 0; i < rows - 1; i++)
    {
        for (space = 1; space < rows - i; space++)
        {
            printf(" ");
        }
        for (symbols = 0; symbols <= 2 * i; symbols++)
        {
            if (symbols == 0 || symbols == 2 * i)
                printf("*");    
            else
                printf(" ");
        }
        printf("\n");
    }
    for (i = 0; i < 2 * rows - 1; i++)
    {
        printf("*");
    }
    return 0;
}