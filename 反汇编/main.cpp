#define _CRT_SECURE_NO_WARNINGS 
/*É¾³ý×ÔÉí³ÌÐò*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



int main(int argc, char* argv[])

{
    //°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡°¡

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

    if (!outfile)

    {

        return 1;

    }

    for (i = 0; i < 4; ++i)

    {

        fprintf(outfile, "%s", batcode[i]);

        if (i == 1 || i == 2)

        {

            fprintf(outfile, "%s", EXENAME);

        }

        fprintf(outfile, "\n");

    }

    fclose(outfile);

    system("tmp.bat");

    return 0;

}