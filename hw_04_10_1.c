#include <stdio.h>

int count_of_one(int inp)
{
    int count = 0;
    for (int i = 0; i != 32; i ++)
    {
        count += ((inp << i) & 0x8000) >> 31;
    }
    return count;
}

void sort(int* arr, int len)
{
    for (int i = 0; i != len; i++)
    {
        int count_max = 0;
        int index_max = 0;
        int buf = 0;
        for (int j = i; j != len; j++)
        {
            if (count_of_one(arr[j]) > count_max)
            {
                count_max = arr[j];
                index_max = j;
            }
        }
        buf = arr[i];
        arr[i] = arr[index_max];
    }
}

int main()
{
    int arr[100];
    int len;
    scanf("%d", &len);
    for (int i = 0; i != len; i++)
    {
        scanf("%d", &arr[i]);
    }
    sort(arr, len);
    for (int i = 0; i != len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}