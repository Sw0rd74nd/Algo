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

void bubbleSort(int *array, int n)
{
   bool swapped;
   for (int i = 0; i < n - 1; i++)
   {
      swapped = false;
      for (int j = 0; j < n - i - 1; j++)
      {
         if (array[j] > array[j + 1])
         {
            swap(&array[j], &array[j + 1]);
            swapped = true;
         }
      }
      if (swapped == false)
      {
         break;
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
   bubbleSort(list, count);
   endTime = GetUSecTime();
   msTime = (endTime - beginTime)/1000;

   for (int i = 0; i < count; i++)
   {
      printf("%d \n", list[i]);
   }

   printf("required time: %lld ms", msTime);

   if (in != stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}
