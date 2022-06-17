#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 99999
const int FLOORLEN = 48 + 1;
const int HASHLEN = 40;
int sum;
int sumlen;
int find(char *sepc, char *buf, FILE *file)
{
    size_t ret;
    int up = sum - 1;
    int down = 0;
    int mid = (up + down) / 2;
    int lastmid = -1;
    fseek(file, sumlen + mid * FLOORLEN, SEEK_SET);
    while ((ret = (size_t)fgets(buf, FLOORLEN, file)) != 0)
    {
        if (memcmp(sepc, buf, HASHLEN) == 0)
        {
            // printf("ok\n");
            return 1;
        }
        else if (memcmp(sepc, buf, HASHLEN) > 0)
        {
            down = mid + 1;
            mid = (up + down) / 2;
            fseek(file, sumlen + mid * FLOORLEN, SEEK_SET);
        }
        else
        {
            up = mid - 1;
            mid = (up + down) / 2;
            fseek(file, sumlen + mid * FLOORLEN, SEEK_SET);
        }
        //printf("up: %d down: %dmid : %d hash:%s\n", up, down, mid, buf);
        if (up <= down + 1)
        {
            break;
        }
    }
    for (int i = down; i <= up; i++)
    {
        fseek(file, sumlen + i * FLOORLEN, SEEK_SET);
        fgets(buf, FLOORLEN, file);
        if (memcmp(sepc, buf, HASHLEN) == 0)
        {
            // printf("ok\n");
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char buf[MAX] = {0};
    char comm[256] = {0};
    char *pid;
    FILE *file;
    if (argc < 3)
    {
        printf("argument num error");
        return -1;
    }
    if (strlen(argv[1]) != 40)
    {
        printf("argument error");
        return -1;
    }
    pid = argv[2];
    file = fopen("hash.txt", "r");
    fgets(buf, 17, file);
    sum = atoi(buf);
    // printf("%s\n",argv[1]);
    sumlen = strlen(buf);
    // printf("sumlen:%d\n",sumlen);
    for (int i = 0; i < sumlen - 1; i++)
    {
        if (buf[i] < 48 || buf[i] > 57)
        {
            printf("sum error");
            return -1;
        }
    }
    // printf("%s\n",argv[1]);
    // fgets(buf,42,file);
    if (find(argv[1], buf, file))
    {
        printf("find and killed %s %s\n", buf, argv[2]);
        sprintf(comm, "kill %s", pid);
        system(comm);
    }
    fclose(file);
    return 0;
}