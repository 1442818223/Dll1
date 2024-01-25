#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

#include <stdlib.h>

#include <string.h>



int main(int argc, char* argv[])

{

    FILE* outfile;

    int i;

    char batcode[][100] = {

        "@echo off",

        "taskkill /f /im ",

        "del /a /q /f ",

        "del %0"

    };

    char EXENAME[10];

    for (i = strlen(argv[0]) - 1; argv[0][i] != '\\'; --i);

    strcpy(EXENAME, &argv[0][i + 1]);

    outfile = fopen("tmp.bat", "wt");


int main(int argc, char* argu[])
{
	
 char c[20] = "dwadawdawdaw";
 char n[20] = { 0 };
int a = 10;


strncpy(n, c, sizeof(n));
printf("%s\n",n);

do {
	a = a + 1;


} while (a < 20);

for (int i = 0; i < 13; i++) {

	w = a * 2 + w;
	int x=10;
	x = x + w;
	printf("%d\n", x);

}

printf("a = %d\n", a);
return 0;
}
