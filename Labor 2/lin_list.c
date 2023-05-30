/*-----------------------------------------------------------------------

Author: Stephan Schulz (schulz@eprover.org)

Copyright 2015 by the author.
  This code is released under the GNU General Public Licence, version
  2, or, at your choice, any later version.

-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE  256

typedef struct lin_list
{
   char            *payload;
   struct lin_list *next;
}LinListCell, *LinList_p;

LinList_p LinListAllocCell(char* payload)
{
/* fill in here, hint: use malloc and strdup*/

    LinList_p cell = malloc(sizeof(LinList_p));
    cell -> payload = strdup(payload);
    cell -> next = NULL;
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

   while(junk)
   {
      next = junk->next;
      LinListFreeCell(junk);
      junk = next;
   }
}

LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell)
{
/* fill in here*/

    newcell -> next = *anchor;
    anchor = &newcell;
    return *anchor;

}

LinList_p LinListExtractFirst(LinList_p *anchor)
{
/* fill in here*/

    LinList_p first = *anchor;
    LinList_p next = first->next;
    LinListFree(first);
    anchor = &next;
    return first;
}

int main(int argc, char *argv[])
{
   FILE *in = stdin;
   char line[MAXLINE];
   LinList_p l1 = NULL, l2=NULL, handle;
   char* inp;

   if(argc > 2)
   {
      fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   if(argc == 2)
   {
      in = fopen(argv[1], "r");
      if(!in)
      {
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }
   }

    
   /* fill in here*/

    while(fgets(line, MAXLINE, in))
    {
        LinList_p cell = LinListAllocCell(line);
        l1 = LinListInsertFirst(&l1, cell);
    }
    
    handle = l1;

    printf("\n==========reverse order========== \n");

    while(handle != NULL)
    { 
        LinList_p newcell = LinListAllocCell(handle -> payload);
        l2 = LinListInsertFirst(&l2, newcell);

        printf("%s", handle -> payload);
        handle = handle -> next;
    }

    handle =l2;

    printf("\n==========original order========== \n");
    
    while(handle != NULL)
    { 
        printf("%s", handle -> payload);
        handle = handle -> next;
    }

   LinListFree(l1);

   if(in!=stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}
