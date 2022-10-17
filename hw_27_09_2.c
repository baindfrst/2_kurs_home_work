#include <stdio.h>
#define size 1

void printMPC(int pr)
{
    for (int i = sizeof(int)*8-1; i >= 0; i--)
    {
        if (((pr>>i) & 1) == 0) printf ("%c ", '0');
        else printf ("%c ", '1');
    }
}

int main()
{
    int a;
    scanf("%d", &a);
    printMPC(a);
    return 0;
}