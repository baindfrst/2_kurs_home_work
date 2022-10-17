#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode {
    int key;
    struct tnode* left, *right;
} tree;

void create (FILE * ffrom, int N);
void writeto (FILE * ffrom, FILE * fto, int N);
void printfile (FILE * fp, int N);
tree * Insert(tree *root, int x);
void tree_write(FILE * ffrom, int N);
void print_tree(tree* root, FILE * ffrom);
void free_tree (tree * root);


int main(int argc, char **argv)
{
    int N, i; char S[strlen(argv[1])+1];
    if (argc < 2) return 1;
    FILE* ffrom, * fto;
    ffrom = fopen (argv[1],"w+b");
    if (ffrom == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    printf("Enter the number of rows\n");
    if ((scanf("%d", &N)!=1) || (N==0))
    {
        printf ("Error reading N");
        return 1;
    }
    create(ffrom, N);
    printfile(ffrom, N);
    i = 0;
    while (*argv[1] != '.')
    {
        S[i] = *argv[1];
        argv[1]++;
        i++;
    }
    S[i] = 'T'; S[i+1] = '.'; S[i+2] = 't'; S[i+3] = 'x';
    S[i+4] = 't'; S[i+5] = '\0';
    printf ("%s\n", S);
    fto = fopen (S, "w+");
    if (fto == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    writeto(ffrom, fto, N);
    tree_write(ffrom, N);
    printf ("vot\n");
    printfile (ffrom, N);
    fclose(ffrom);
    fclose(fto);

    return 0;
}

void create (FILE * ffrom, int N)
{
    int i, len, elem, j, zero = 0;
    len = 1 + rand()%(N/2 +2);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < len; j++)
        {
            elem = 1+ rand()%N;
            fwrite (&elem, sizeof(int), 1, ffrom);
            printf("This elem %d ", elem);
        }
        fwrite (&zero, sizeof(int), 1, ffrom);
        printf ("\n");
        len = 1 + rand()%(N/2 +2);
    }
}

void writeto (FILE * ffrom, FILE * fto, int N)
{
    int c, i = 0;
    char a;
    int flag = 1;
    if (feof(ffrom))
    {
        printf("File is empty");
        exit(1);
    }
    fseek(ffrom, 0, SEEK_SET); //�������� ��������� �� ������ �����
    while (i != N)
    {
        fread (&c, sizeof(int), 1, ffrom);
        if (c != 0)
        {
            //��������� � ������
            a = c + '0';
            if (!flag) fprintf(fto, " ");
            fwrite (&a, sizeof(char), 1, fto);
            flag = 0;
        }
        else
        {
            fprintf(fto, "\n");
            flag = 1;
            i++;
        }
    }
}

void printfile (FILE * fp, int N)
{
    int elem, i = 0;
    fseek(fp, 0, SEEK_SET); //�������� ��������� �� ������ �����
    printf("Print from file\n");
    while (i != N)
    {
        fread(&elem, sizeof(int), 1, fp);
        printf("This elem %d ", elem);
        if (elem == 0)
        {
            i++;
            printf ("\n");
        }

    }
}
tree * Insert(tree *root, int x)
{
    if (root==NULL)
    {
        root = malloc(sizeof(tree));
        root->key = x;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if (x < root->key)
            root->left = Insert(root->left, x);
        else
            root->right = Insert(root->right, x);

    }
    return root;
}
void tree_write(FILE * ffrom, int N)
{
    int i = 0, elem, pos, to_start;
    tree * root;
    fseek(ffrom, 0, SEEK_SET);//�������� ��������� �� ������ �����
    to_start = ftell(ffrom);
    while (i != N)
    {
        root = NULL;
        fread(&elem, sizeof(int), 1, ffrom);
        while (elem != 0)
        {
            //���������� ������
            root =Insert(root, elem);
            fread(&elem, sizeof(int), 1, ffrom);
        }
       i++;
       pos = ftell(ffrom);
       printf("This is sortied tree: ");
       fseek (ffrom, to_start, SEEK_SET);
       print_tree(root, ffrom);
       printf("\n");
       fseek (ffrom, pos, SEEK_SET);
       to_start = ftell(ffrom);
       free_tree(root);
    }
    printf ("pizda\n");

}

void print_tree(tree* root, FILE * ffrom)
{
    if (root)
    { //���� �� ���������� ������ ����
        print_tree(root->right, ffrom);
        printf ("%d ", root->key);//���������� ������ ������
        //fseek(ffrom, -pos, SEEK_SET);
        fwrite(&root->key, sizeof(int), 1, ffrom);
        print_tree(root->left, ffrom);
    }
}

void free_tree (tree * root)
{
    if (root)
    {
        free_tree(root->right);
        free_tree(root->left);
        free(root);
    }
}


