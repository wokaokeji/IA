#include <stdlib.h>
#include <stdio.h>

#define ALIGN(a, b) (a + b -1)&(~(b - 1))

int main()
{
	int in;
	while(EOF != scanf("%d", &in))
	{
		printf("\t%d align:\t%d\n", in, ALIGN(in, 8));
	}
	if(0)
		;
	else
	{
		printf("0"												\
				  "asdf\n");
	}
	return 0;
}
