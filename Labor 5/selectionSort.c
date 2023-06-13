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

void swap(int *u, int *v)
{
    int temp = *u;
    *u = *v;
    *v = temp;
}

void selectionSort(int *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {

            if (array[j] < array[min])
            {

                min = j;
            }

            if (min != i)
            {

                swap(&array[min], &array[i]);
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
    long long beginTime, endTime, msTime;

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
    msTime = (endTime - beginTime) / 1000;

    if (count <= 20)
    {
        for (int i = 0; i < count; i++)
        {
            printf("%d \n", list[i]);
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            printf("%d \n", list[i]);
        }

        printf("...\n");

        for (int i = count - 5; i < count; i++)
        {
            printf("%d \n", list[i]);
        }
    }

    printf("\n------SelectionSort------\n");
    printf("required time: %lld mssec \n", msTime);

    free(list);

    if (in != stdin)
    {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}