#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
int w = 3000;


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
