#include<stdio.h>
void pr(int*);

main()
{
	int a[10] = { 0,1,2,3 };
	pr(&a);
}

void pr(int *x)
{
	printf("%d %d %d %d", *(x + 1), x + 2, x + 3, x + 4);
	return;
}
