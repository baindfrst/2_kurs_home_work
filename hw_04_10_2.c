#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct list
{
    char* elem;
    struct list* next;
    struct list* prev;
} list;

list* init_list(list* next, list* prev, char* data)
{
    list* out = malloc(sizeof(list));
    out->elem = data;
    out->next = next;
    out->prev = prev;
    return out;
}

void del_list(list* to_del)
{
    while (to_del->prev != NULL)
    {
        to_del = to_del->prev;
    }
    while(!to_del)
    {
        list* del = to_del;
        to_del = to_del->next;
        free(del);
    }
}

void print_list(list* inp)
{
    list* rez = inp;
    while (rez->prev != NULL)
    {
        rez = rez->prev;
    }
    while(rez)
    {
        printf("|| %s ||", rez->elem);
        rez = rez->next;
    }
    printf("\n");
}

void paste_past_num(list* arr)
{
    int to_start = 0;
    while(arr->prev != NULL)
    {
        arr = arr->prev;
        to_start++;
    }
    int num_paste;
    if (arr->next == NULL && arr->prev == NULL && arr->elem == NULL)
    {
        printf("ERROR");
        exit(-1);
    }
    printf("num to paste: ");
    scanf("%d", &num_paste);
    printf("string: ");
    char *S = malloc(N*sizeof(char));
    int i = 0;
    int j = 1;
    int c;
    getchar();
    while (((c=getchar()) != '\n') && (c != EOF))
    {
        S[i] = (char)c;
        i++;
        if (N * j == i)
        {
            S = realloc(S, ((sizeof(char))*(N + N*j)));
            j++;
        }
    }
    S[i] = '\0';
    for(int i = 0; i != num_paste; i++)
    {
        if(arr->next == NULL) // если количество строк меньше, чем введеное число.
        {
            printf("ERROR");
            for (int j; j != i; j ++)
            {
                arr = arr->prev;
            }
            exit(-1);
        }
        arr = arr->next;
    }
    list* incl = init_list(arr->next, arr, S);
    if (arr->next != NULL)
    {
        arr->next->prev = incl;
    }
    arr->next = incl;
    if ((num_paste + 1) >= to_start)
    {
        to_start++;
    } 
    while(arr->prev != NULL)
    {
        arr = arr->prev;
    }
    for (int i = 0; i != to_start; i++)
    {
        arr = arr->next;
    }
}

void del_elem(list* arr)
{
    int to_start = 0;
    while(arr->prev != NULL)
    {
        arr = arr->prev;
        to_start++;
    }
    int num;
    printf("num for del: ");
    if (arr->next == NULL && arr->prev == NULL && arr->elem == NULL)
    {
        printf("ERROR");
        exit(-1);
    }
    scanf("%d", &num);
    for(int i = 0; i != num; i++)
    {
        if(arr->next == NULL) // если количество строк меньше, чем введеное число.
        {
            printf("ERROR");
            for (int j; j != i; j ++)
            {
                arr = arr->prev;
            }
            exit(-1);
        }
        arr = arr->next;
    }
    list* del;
    del = arr;
    if (arr->next == NULL && arr->prev == NULL)
    {
        arr = NULL;
    }
    else
    {
        if (arr->next == NULL)
        {
            arr = arr->prev;
            arr->next = NULL;
        }
        else
        {
            if(arr->prev == NULL)
            {
                arr = arr->next;
                arr->prev = NULL;
            }
            else
            {
                arr = arr->next;
                arr->prev = del->prev; 
                del->prev->next = arr;
            }
        }
    }
    free(del);
    if (!((num + 1) >= to_start))
    {
        to_start--;
    } 
    while(arr->prev != NULL)
    {
        arr = arr->prev;
    }
    for (int i = 0; i != to_start; i++)
    {
        arr = arr->next;
    }
}

int main()
{
    list* main_list;
    main_list = init_list(NULL, NULL, NULL);
    while(1)
    {
        list* added;
        
        char* input;
        int memory = 1;
        int added_blocks = 1;
        int readed;
        input = malloc(N * sizeof(char) * added_blocks);
        while (((readed = getchar()) != '\n') && readed != EOF && (char)readed != ' ')
        {
            if (memory == (N + 1))
            {
                input = realloc(input, N * added_blocks);
                added_blocks++;
                memory = 1;
            }
            input[(added_blocks == 1)?(memory - 1):(memory + ((added_blocks - 1) * 4 - 1))] = (char)readed;
            memory++;
            input[(added_blocks == 1)?(memory - 1):(memory + ((added_blocks - 1) * 4 - 1))] = '\0';
        }
        if (memory == (N + 1))
        {
            input = realloc(input, N * added_blocks);
            added_blocks++;
            memory = 1;
        }
        input[(added_blocks == 1)?(memory - 1):(memory + ((added_blocks - 1) * 4 - 1))] = '\0';
        if ((readed == '\n' && input[0] != 0) || (readed == EOF && input[0] != 0))
        {
            if (main_list->elem != NULL)
            {
                added = init_list(NULL, main_list, input);
                main_list->next = added;
                main_list = main_list->next;
            }
            else
            {
                main_list->elem = input;
            }
            break;
        }
        else
        {
            if ((readed == '\n' && input[0] == 0) || (readed == EOF && input[0] == 0))
            {
                free(input);
                break;
            }
            else
            {
                if (main_list->elem != NULL)
                {
                    added = init_list(NULL, main_list, input);
                    main_list->next = added;
                    main_list = main_list->next;
                }
                else
                {
                    main_list->elem = input;
                }
            }
        }
    }
    void (*operation_arr[3])(list*) = {print_list, paste_past_num, del_elem};
    int stop_flag = 1;
    while (stop_flag)
    {
        operation_arr[0](main_list);
        operation_arr[1](main_list);
        operation_arr[0](main_list);
        operation_arr[2](main_list);
        operation_arr[0](main_list);
        printf("paste 0 to end: ");
        scanf("%d", &stop_flag);
    }
    del_list(main_list);
    return 0;
}