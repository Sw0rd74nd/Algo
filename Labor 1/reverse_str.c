#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_str(char* c) 
{
    FILE* fp = fopen(c, "r");
   
    char lines[100][100];
    char line[100];
    int numLines = 0;

    while (fgets(line, sizeof(line), fp)) 
    {
        strcpy(lines[numLines], line);
        numLines++;
    }
    
    for (int i = numLines - 1; i >= 0; i--) 
    {
        printf("%s", lines[i]);
    }
}

int main(int agrc, char **argv) 
{ 
    reverse_str(argv[1]);
    return 0;
}
