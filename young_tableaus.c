#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <assert.h>

#define RAND_GEN

#define MAX_SIZE 8
#define MAX_NUM 1<<30




int extract_min(int y[MAX_SIZE][MAX_SIZE]);
int young_heapify(int y[MAX_SIZE][MAX_SIZE], int a, int b);
int young_rheapify(int y[MAX_SIZE][MAX_SIZE], int a, int b);
int young_insert(int y[MAX_SIZE][MAX_SIZE], int elm);
int young_search(int y[MAX_SIZE][MAX_SIZE], int elm, int *p, int *q);

int swap(int *x, int *y);
int disp_young(int y[MAX_SIZE][MAX_SIZE]);

int y[MAX_SIZE][MAX_SIZE];
int mat[]={32,42,3,45,2,2,27,28,22,42,23,32,37,41,45,19,45,8,21,5,49,46,48,44,19,4,38,2,16,31,9,48,25,12,46,27};


int main()
{
	srand(time(NULL));
	
	int i, j;
	for(i = 0; i < MAX_SIZE; i++)
	{
		for(j = 0; j < MAX_SIZE; j++)
		{
			y[i][j] = MAX_NUM;
		}
	}
	
	//y[0][0] = 51;
	disp_young(y);

#ifdef RAND_GEN
	int len = 60;
#else
	int len = sizeof(mat)/sizeof(mat[0]);
#endif
	//int len = 4;
	int ite = 0;
	while(ite++ < len)
	{
		int elm = rand()%64;
#ifdef RAND_GEN
		printf("index:%d, young_insert %d\n", ite, elm);
		young_insert(y, elm);
#else
		printf("index:%d, young_insert %d\n", ite, mat[ite - 1]);
		young_insert(y, mat[ite - 1]);
#endif
		disp_young(y);
	}
	
	disp_young(y);
	int p , q;
	young_search(y, 51, &p, &q);
	printf("young_search(y,51,&p,&q)= (%d %d)\n", p, q);	
	
	
	printf("extract_min()\n");
	ite = 0;
	while(ite++ < 64)
	{
		printf("%.3d:extract_min:\t%d\n", ite, extract_min(y));
	}

	return 0;
}

int extract_min(int y[MAX_SIZE][MAX_SIZE])
{
	int val = y[0][0];
	y[0][0] = y[MAX_SIZE - 1][MAX_SIZE - 1];
	young_heapify(y, 0, 0);

	return val;
}



int young_heapify(int y[MAX_SIZE][MAX_SIZE], int a, int b)
{
	int i = a,
			j = b;
	if( a < MAX_SIZE - 1 && y[a + 1][b] < y[i][j])
	{
		i++;
	}
	if( b < MAX_SIZE - 1 && y[a][b + 1] < y[i][j])
	{
		i = a;
		j++;
	}

	if(i == a && j == b)
	{
		return 0;
	}
	swap(&y[i][j], &y[a][b]);
	young_heapify(y, i, j);
	return 1;
}


int young_insert(int y[MAX_SIZE][MAX_SIZE], int elm)
{
	if(y[MAX_SIZE - 1][MAX_SIZE - 1] != MAX_NUM)
	{
		fprintf(stderr, "%dERROR:young_insert()\n", __LINE__);
		return -1;
	}
	y[MAX_SIZE - 1][MAX_SIZE - 1] = elm;	
	young_rheapify(y, MAX_SIZE - 1, MAX_SIZE - 1);
}

int young_rheapify(int y[MAX_SIZE][MAX_SIZE], int a, int b)
{
	int i = a,
			j = b;
	if( a > 0 && y[a - 1][b] > y[i][j])
	{
		i--;
	}
	if( b > 0 && y[a][b - 1] > y[i][j])
	{
		i = a;
		j--;
	}

	if(a == i && b == j)
	{
		return 0;
	}
	swap(&y[i][j], &y[a][b]);
	young_rheapify(y, i, j);

	return 1;
}

int swap(int *x, int *y)
{
	if(*x == *y)
	{
		return 0;
	}

	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;

}

int young_search(int y[MAX_SIZE][MAX_SIZE], int elm, int *p, int *q)
{
	int i = 0,
			j = MAX_SIZE - 1;

	*p = -1;
	*q = -1;
	while(i < MAX_SIZE && j >= 0)
	{
		if(elm == y[i][j])
		{
			*p = i;
			*q = j;
			return 0;
		}
		else if(i < MAX_SIZE - 1 && elm > y[i][j])
		{
			i++;
		}
		else if(j > 0 && elm < y[i][j])
		{
			j--;
		}
		else
		{
			return -1;
		}
	}

	return -1;

}

int disp_young(int y[MAX_SIZE][MAX_SIZE])
{
	int i, j;
	for(i = 0; i < MAX_SIZE; i++)
	{
		for(j = 0; j < MAX_SIZE; j++)
		{
			printf("%10d  ",y[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
