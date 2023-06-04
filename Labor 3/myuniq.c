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

LinList_p LinListInsertLast(LinList_p *anchor, LinList_p newcell)
{
   LinList_p current = *anchor;
   while (current->next != NULL)
   {
      current = current->next;
   }
   current->next = newcell;
   return newcell;
}

LinList_p LinListExtractLast(LinList_p *anchor)
{

   LinList_p current = *anchor;
   while (current->next->next != NULL)
   {
      current = current->next;
      current->next = NULL;
   }
   return current;
}

LinList_p LinListExtract(LinList_p *anchor, LinList_p cell)
{
   (*anchor)->next = cell->next;
   return *anchor;
}

int main(int argc, char *argv[])
{
   FILE *in = stdin;
   char line[MAXLINE];
   LinList_p l1 = NULL, l2 = NULL, handle;
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

   int listLen = 0;

   while (fgets(line, MAXLINE, in))
   {
      LinList_p cell = LinListAllocCell(line);
      l1 = LinListInsertFirst(&l1, cell);
      listLen++;
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

   char arr[listLen][MAXLINE];
   strcpy(arr[0], l2->payload);

   handle = l2->next;

   for (int i = 0; i < listLen; i++)
   {
      for (int j = 0; j < listLen; j++)
      {
         if (handle->payload == arr[j])
         {
            LinListExtract(l2, handle);
         }
      }
   }

   printf("\n==========no duplicates========== \n");

   while (handle != NULL)
   {
      printf("%s", handle->payload);
      handle = handle->next;
   }

   LinListFree(l1);
   LinListFree(l2);

   if (in != stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}
