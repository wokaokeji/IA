#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int swap(int *m, int *n);
int shuffle_array(int a[], int len);
int quick_sort(int a[], int p, int q);
int partition(int a[], int p, int q);
int disp_array(int a[], int len);

int main()
{
	srand(time(NULL));
	int a[]={1,2,3,4,5,6,7,8,9,2,3};
	int len = sizeof(a)/sizeof(a[0]);
	disp_array(a, len);
	
	shuffle_array(a, len);
	disp_array(a, len);

	quick_sort(a, 0, len - 1);
	disp_array(a, len);

	return 0;
}

int swap(int *m, int *n)
{
	if(m == n)
	{
		return 0;
	}
	*m = *m ^ *n;
	*n = *m ^ *n;
	*m = *m ^ *n;

	return 1;
}

int shuffle_array(int a[], int len)
{
	int i;
	while(len)
	{
		i = rand()%(len--);
		swap(&a[i],&a[len]);
	}

	return 0;
}

int quick_sort(int a[], int p, int q)
{
	if(p >= q)
	{
		return 0;
	}
	int mid;
	mid = partition(a, p ,q);
	quick_sort(a, p, mid - 1);
	quick_sort(a, mid + 1, q);

	return 0;
}

int partition(int a[], int p, int q)
{
	int key = a[q];
	int i, j = p;
	for(i = p; i < q; i++)
	{
		if(a[i] < key)
		{
			swap(&a[j], &a[i]);
			j++;
		}
	}
	swap(&a[q],&a[j]);

	return j;
}

int disp_array(int a[], int len)
{
	int i;
	for(i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
