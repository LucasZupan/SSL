#include <stdio.h>

int main()
{
    FILE *opening;
    opening = fopen("hello.txt", "w");
    fprintf(opening, "Hello world!");
    fclose(opening);

    return 0;
}
