#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int file_size(int fd)
{
    char readed;
    int len = 0;
    while (read(fd, &readed, 1) > 0)
    {
        len++;
    }
    lseek(fd, 0, SEEK_SET);
    return len;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("error input");
        return 1;
    }
    char* file_name = argv[1];
    int N = 0;
    for (int i = 0; argv[2][i] != '\0'; i++)
    {
        if (N == 0)
        {
            N = argv[2][i] - '0';
        }
        else
        {
            N = N * 10 + argv[2][i] - '0';
        }
    }
    int fd = open(file_name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd<0)
    {
        printf("err open file");
        return -1;
    }

    int file_size_cur = file_size(fd);
    printf("%d", file_size_cur);
    if (file_size_cur >= 1024)
    {
        printf("no changes");
        return 0;
    }

    int les = file_size_cur - (file_size_cur / N) * N;
    char* reading = malloc(sizeof(sizeof(char) * les));
    lseek(fd, -les, SEEK_END);
    read(fd, reading, les);
    lseek(fd, 2 * (file_size_cur - les), SEEK_SET);
    write(fd, reading, les);
    reading = realloc(reading, N);
    for (int i = 1; i != (file_size_cur / N) + 1; i++)
    {
        lseek(fd, file_size_cur - les - N*i, SEEK_SET);
        read(fd, reading, N);
        lseek(fd, 2 * (file_size_cur - les - N*i), SEEK_SET);
        write(fd, reading, N);
        write(fd, reading, N);
    }
    close(fd);
    return 0;
}