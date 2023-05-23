#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void rand_seq(int t)
{
    int MAXNUM = 1000;
    srand(time(NULL));
    for (int i = 0; i < t; i++)
    {
        int r = rand() % MAXNUM;
        printf( "%d \n", r);
        
    }

}

int main(int argc, char *argv[])
{
    char *a = argv[1];
    int num = atoi(a);
    rand_seq(num);
    
    return 0;
}
