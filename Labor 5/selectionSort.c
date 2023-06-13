#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAXLINE 1000000

long long GetUSecTime()
{
    clock_t cpuTime = clock();
    return (long long)cpuTime * 1000000 / CLOCKS_PER_SEC;
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int *array, int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {

            if (array[j] < array[min_idx])
            {

                min_idx = j;
            }

            if (min_idx != i)
            {

                swap(&array[min_idx], &array[i]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *in = stdin;
    char line[MAXLINE];
    int count = 0;
    int *list;
    long long beginTime, endTime, msTime, uTime;

    list = malloc(100000 * sizeof(int));

    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    while (fgets(line, sizeof(line), in))
    {
        list[count++] = atoi(line);
    }

    list = realloc(list, count * sizeof(int));

    beginTime = GetUSecTime();
    selectionSort(list, count);
    endTime = GetUSecTime();
    uTime = endTime - beginTime;
    msTime = (endTime - beginTime) / 1000;

    for (int i = 0; i < count; i++)
    {
        printf("%d \n", list[i]);
    }

    printf("\n------SelectionSort------\n");
    printf("required time: %lld mssec \n", msTime);
    printf("required time: %lld usec \n", uTime);
    printf("begin time: %lld usec \n", beginTime);
    printf("end time: %lld usec \n", endTime);

    free(list);

    if (in != stdin)
    {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}