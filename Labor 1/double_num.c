#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void double_num(char* c)
{
    FILE* fp = fopen (c, "r");

    char line[100];

    while( fgets(line, sizeof(line), fp))
    {
        printf("%d \n", atoi(line)*2);
    }

}

int main(int argc, char **argv)
{
    double_num(argv[1]);
    return 0;
}