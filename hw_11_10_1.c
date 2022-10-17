#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int key;
    struct tree* left;
    struct tree* right;
} tree;

void print_file(char* name)
{
    FILE* f;
    char* name_file = malloc(strlen(name)*sizeof(char));
    name_file = strcpy(name_file, name);
    f = fopen(strcat(name_file, ".bin"), "r");
    int readed;
    fread(&readed, sizeof(int), 1, f);
    while (readed != '\n' && readed != EOF)
    {
        printf("%d ", readed);
        fread(&readed, sizeof(int), 1, f);
    }
    free(name_file);
}

void add_to_tree(tree* obj, int elem)
{
    if (elem > obj->key)
    {
        if (obj->right != NULL)
        {
            add_to_tree(obj->right, elem);
        }
        else
        {
            tree* create = malloc(sizeof(tree));
            create->key = elem;
            create->right = NULL;
            create->left = NULL;
            obj->right = create;
        }
    }
    else
    {
        if (obj->left != NULL)
        {
            add_to_tree(obj->left, elem);
        }
        else
        {
            tree* create = malloc(sizeof(tree));
            create->key = elem;
            create->left = NULL;
            create->right = NULL;
            obj->left= create;
        }
    }
}

void free_tree(tree* input)
{
    if(input->left != NULL)
    {
        free_tree(input->left);
    }
    if(input->right != NULL)
    {
        free_tree(input->right);
    }
    free(input);
}

void print_tree_to_file(FILE* file_inp, tree* from)
{
    if(from->right != NULL && from->left != NULL)
    {
        int pr = from->key;
        print_tree_to_file(file_inp, from->right);
        fwrite(&pr, sizeof(int), 1, file_inp);
        print_tree_to_file(file_inp, from->left);
    }
    else
    {
        if(from->left == NULL && from->right != NULL)
        {
            int pr = from->key;
            print_tree_to_file(file_inp, from->right);
            fwrite(&pr, sizeof(int), 1, file_inp);
        }
        else
        {
            if(from->left != NULL && from->right == NULL)
            {
                int pr = from->key;
                fwrite(&pr, sizeof(int), 1, file_inp);
                print_tree_to_file(file_inp, from->left);
            }
            else
            {
                int pr = from->key;
                fwrite(&pr, sizeof(int), 1, file_inp);
            }
        }
    }
}

void posled_1(char* name)
{
    FILE* file_in;
    char* name_file = malloc(strlen(name)*sizeof(char) + 4);
    name_file = strcpy(name_file, name);
    name_file = strcat(name_file, ".bin");
    file_in = fopen(name_file, "w");
    int n;
    scanf("%d", &n);
    getchar();
    int input;
    for (int i = 0; i != n; i++)
    { 
        while((input = getchar()) != '\n' && input != EOF)
        {
            int number = 0;
            while(input != (int)' ' && input != '\n' && input != EOF)
            {
                if (number == 0)
                {
                    number = input - (int)'0';
                }
                else
                {
                    number = number * 10 + (input - (int)'0');
                }
                input = getchar();
            }
            fwrite(&number, sizeof(int), 1, file_in);
            if (input != ' ')
            {
                break;
            }
        }
        if(i != n-1)
        {
            int zero = 0;
            fwrite(&zero, sizeof(int), 1, file_in);
        }
    }
    int end = EOF;
    fwrite(&end , sizeof(end), 1, file_in);
    fclose(file_in);
    free(name_file);
}

void posled_2(char* name)
{
    char* name_scnd_file = malloc(sizeof(char)*(strlen(name) + 1));
    char* name_file = malloc(strlen(name)*sizeof(char) + 1);
    name_file = strcpy(name_file, name);
    name_scnd_file = strcpy(name_scnd_file, name);
    name_scnd_file = strcat(name_scnd_file, "T");
    FILE* file_in;
    FILE* file_out;
    if ((file_in = fopen(strcat(name_file, ".bin"), "r")) == NULL)
    {
        printf("no file");
        exit(-1);
    }
    file_out = fopen(strcat(name_scnd_file, ".txt"), "w");
    int readed;
    fread(&readed, sizeof(int), 1, file_in);
    while (readed != '\n' && readed != EOF)
    {
        if (readed != 0)
        {
            fprintf(file_out, "%d ", readed);
        }
        else
        {
            fprintf(file_out,"%c" ,'\n');
        }
        fread(&readed, sizeof(int), 1, file_in);
    }
    fclose(file_in);
    fclose(file_out);
    free(name_file);
    free(name_scnd_file);
}

void posled_3(char* name)
{
    FILE* file_in;
    char* name_file = malloc(strlen(name)*sizeof(char) + 1);
    name_file = strcpy(name_file, name);
    if ((file_in = fopen(strcat(name_file, ".bin"), "r+")) == NULL)
    {
        printf("no file");
        exit(-1);
    }
    int readed;
    fread(&readed, sizeof(int), 1, file_in);
    int back_prev = 0;
    while (readed != '\n' && readed != EOF)
    {
        tree* cur = malloc(sizeof(tree));
        int back_to;
        int start = 0;
        while (readed != 0 && readed != '\n' && readed != EOF)
        {
            if (start == 0)
            {
                cur->key = readed;
                start++;
                cur->left = NULL;
                cur->right = NULL;
            }
            else
            {
                add_to_tree(cur, readed);
            }
            fread(&readed, sizeof(int), 1, file_in);
        }
        back_to = ftell(file_in);
        fseek(file_in, back_prev, SEEK_SET);
        print_tree_to_file(file_in, cur);
        back_prev = back_to;
        free_tree(cur);
        fseek(file_in, back_prev, SEEK_SET);
        fread(&readed, sizeof(int), 1, file_in);

    }
    fclose(file_in);
    free(name_file);
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("Error");
        exit(-1);
    }
    char* name_file = argv[1];
    posled_1(name_file);
    print_file(name_file);
    posled_2(name_file);
    posled_3(name_file);
    printf("\n");
    print_file(name_file);
    posled_2(name_file);
    
    return 0;
}