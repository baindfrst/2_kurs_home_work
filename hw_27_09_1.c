#include <stdio.h>
#include <string.h>
#define size 4

int read_string()
{
    char* string;
    int memory;
    char readed;
    string = malloc(size);
    scanf("%c", &string);

}

int main()
{
    char* string;
    char readed;
    string = malloc(sizeof(char)*size);
    scanf("%c", &string);
    strcat(string, getchar());
    printf("%s", string);
    return 0;
}