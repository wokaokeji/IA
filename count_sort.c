#include <stdio.h>
#include <stdlib.h>


int count_sort(int src[], int dst[], int len, int max_num);
int disp_array(int a[], int len);

int main()
{
	int src_array[] = {5,4,5,1,3,2,8,4,2,5,6,1,5,6,9,1,5,4,8};
	//int src_array[] = {1,3,5,7,9,8,6,4,2,0};
	int len = sizeof(src_array)/sizeof(src_array[0]);
	int *dst_array = calloc(len, sizeof(int));	
	disp_array(src_array, len);
	count_sort(src_array, dst_array, len, 20);
	disp_array(dst_array, len);
	free(dst_array);	
	return 0;
}

int count_sort(int src[], int dst[], int len, int max_num)
{
	int *c = calloc(max_num, sizeof(int));
	int i;
	for(i = 0; i < len; i++)
	{
		c[src[i]]++;
	}

	for(i = 1; i < max_num; i++)
	{
		c[i] += c[i - 1];
	}
	
	disp_array(c, max_num);

	for(i = len; i >= 0; i--)
	{
		dst[--c[src[i]]] = src[i];
	}
	disp_array(c, max_num);
	free(c);
	return 0;
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
