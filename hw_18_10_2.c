#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int file_size(int fd)
{
    char readed;
    int len = 0;
    lseek(fd, 0, SEEK_SET);
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
    char* string_to_del = argv[2];
    int fd = open(file_name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd<0)
    {
        printf("err open file");
        return -1;
    }

    int start_del_pos, end_del_pos;
    int start_check = 0;
    int cur_pos = 0;
    int back_pos = 0;
    char readed;
    int len_file = file_size(fd);
    int deling = 0;
    while(cur_pos != len_file)
    {
        read(fd, &readed, 1);
        cur_pos++;
        if(string_to_del[start_check] == '\0')
        {
            back_pos = start_del_pos;
            while (cur_pos != len_file + 1)
            {
                lseek(fd, start_del_pos, SEEK_SET);
                write(fd, &readed, 1);
                lseek(fd, cur_pos, SEEK_SET);
                read(fd, &readed, 1);
                cur_pos++;
                start_del_pos++;
            }
            cur_pos = back_pos - 1;
            lseek(fd, cur_pos, SEEK_SET);
            start_check = 0;
            len_file -= (strlen(string_to_del));
            deling++;
        }
        else
        {
            if(readed == string_to_del[start_check])
            {
                if (start_check == 0)
                {
                    start_del_pos = cur_pos - 1;
                }
                start_check++;
            }
            else
            {
                start_check = 0;
            }
        }
    }
    if(string_to_del[start_check] == '\0')
    {
        len_file -= strlen(string_to_del);
    }
    ftruncate(fd, len_file);  
    close(fd);
    return 0;
}