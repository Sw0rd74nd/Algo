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

int partition(int *array, int low, int high)
{

   int pivot = array[high];

   int i = (low - 1);

   for (int j = low; j <= high - 1; j++)
   {

      if (array[j] < pivot)
      {
         i++;
         swap(&array[i], &array[j]);
      }
   }
   swap(&array[i + 1], &array[high]);
   return (i + 1);
}

void quickSort(int *array, int low, int high)
{
   if (low < high)
   {
      int pi = partition(array, low, high);

      quickSort(array, low, pi - 1);
      quickSort(array, pi + 1, high);
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
   quickSort(list, 0, count - 1);
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

   printf("\n------QuickSort------\n");
   printf("required time: %lld mssec \n", msTime);

   free(list);

   if (in != stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}
