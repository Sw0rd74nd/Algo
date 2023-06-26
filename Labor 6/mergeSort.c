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

void merge(int arr[], int l, int m, int r)
{
   int i;
   int j;
   int k;
   int x = m - l + 1;
   int y = r - m;

   int *Left = (int *)malloc(x * sizeof(int));
   int *Right = (int *)malloc(y * sizeof(int));

   for (i = 0; i < x; i++)
   {
      Left[i] = arr[l + i];
   }

   for (j = 0; j < y; j++)
   {
      Right[j] = arr[m + 1 + j];
   }

   i = 0;
   j = 0;
   k = l;

   while (i < x && j < y)
   {
      if (Left[i] <= Right[j])
      {
         arr[k] = Left[i];
         i++;
      }
      else
      {
         arr[k] = Right[j];
         j++;
      }
      k++;
   }

   while (i < x)
   {
      arr[k] = Left[i];
      i++;
      k++;
   }

   while (j < y)
   {
      arr[k] = Right[j];
      j++;
      k++;
   }

   free(Left);
   free(Right);
}

void mergeSort(int arr[], int l, int r)
{
   if (l < r)
   {
      int m = l + (r - l) / 2;

      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);

      merge(arr, l, m, r);
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
   mergeSort(list, 0, count - 1);
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

   printf("\n------MergeSort------\n");
   printf("required time: %lld mssec \n", msTime);

   free(list);

   if (in != stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}