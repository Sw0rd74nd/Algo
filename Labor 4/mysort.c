#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256

typedef struct lin_list
{
   char *payload;
   struct lin_list *next;
} LinListCell, *LinList_p;

LinList_p LinListAllocCell(char *payload)
{
   LinList_p cell = malloc(sizeof(LinList_p));
   cell->payload = strdup(payload);
   cell->next = NULL;
   return cell;
}

void LinListFreeCell(LinList_p junk)
{
   free(junk->payload);
   free(junk);
}

void LinListFree(LinList_p junk)
{
   LinList_p next;

   while (junk)
   {
      next = junk->next;
      LinListFreeCell(junk);
      junk = next;
   }
}

LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell)
{
   newcell->next = *anchor;
   anchor = &newcell;
   return *anchor;
}

LinList_p LinListExtractFirst(LinList_p *anchor)
{

   LinList_p first = *anchor;
   LinList_p next = first->next;
   LinListFree(first);
   anchor = &next;
   return first;
}

LinList_p LinListSort(LinList_p* anchor)
{
   LinList_p handle = *anchor;
   LinList_p temp, prev, next;
   int swapped = 1;

   while (swapped)
   {
      swapped = 0;
      temp = handle;
      prev = NULL;

      while (temp != NULL && temp->next != NULL)
      {
         if (strcmp(temp->payload, temp->next->payload) > 0)
         {
            next = temp->next;

            if (prev != NULL)
               prev->next = next;
            else
               handle = next;

            temp->next = next->next;
            next->next = temp;

            prev = next;
            swapped = 1;
         }
         else
         {
            prev = temp;
            temp = temp->next;
         }
      }
   }

   *anchor = handle;
   return handle;
}

int main(int argc, char *argv[])
{
   FILE *in = stdin;
   char line[MAXLINE];
   LinList_p l1 = NULL, l2 = NULL, handle, l3 = NULL;
   char *inp;

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

   while (fgets(line, MAXLINE, in))
   {
      LinList_p cell = LinListAllocCell(line);
      l1 = LinListInsertFirst(&l1, cell);
   }

   handle = l1;

   while (handle != NULL)
   {
      LinList_p newcell = LinListAllocCell(handle->payload);
      l2 = LinListInsertFirst(&l2, newcell);

      handle = handle->next;
   }

   handle = l2;

   printf("\n==========original order========== \n");

   while (handle != NULL)
   {
      printf("%s", handle->payload);
      handle = handle->next;
   }

   l3 = LinListSort(&l2);
   handle = l3;

   printf("\n==========sorted order============ \n");

   while (handle != NULL)
   {
      printf("%s", handle->payload);
      handle = handle->next;
   }

   LinListFree(l1);

   if (in != stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}
