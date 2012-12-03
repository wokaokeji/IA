#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 512
#define LEFT(i) (((i)<<1) + 1)
#define RIGHT(i) (((i) + 1)<<1)
//#define LEFT(i) ((i)*2 + 1)
//#define RIGHT(i) (((i) + 1)*2)
#define PARENT(i) ((i - 1)>>1)

typedef struct {
	int id;
	int level;
	char describe[16];
}thread_info_t;


int insert(thread_info_t heap[], int len, thread_info_t *elm);
thread_info_t* maximum(thread_info_t heap[], int len);
int extract_max(thread_info_t heap[], int len, thread_info_t *elm);
int increase_key(thread_info_t heap[],int len, int index, int key);

int build_max_heap(thread_info_t heap[], int len);
int max_heapify(thread_info_t heap[], int len, int index);

int heap_sort(thread_info_t heap[], int len);
int disp_heap(thread_info_t heap[], int len);
int disp_heap_order(thread_info_t heap[], int len);
int swap(thread_info_t *x, thread_info_t *y);

int main()
{

	int level[] = {1,3,5,7,9,0,8,6,4,2,1,4,7,0,9,4,8,2,3,5,8,9,0,5,1,5,2,8};
	int len = sizeof(level)/sizeof(level[0]);
	thread_info_t *heap = calloc(MAX_LEN, sizeof(thread_info_t));
	int i;
	for(i = 0; i < len; i++)
	{
		heap[i].id = i;
		heap[i].level = level[i];
		sprintf(heap[i].describe, "thread_%.3d", i);
	}
	disp_heap(heap, len);

	printf("build_max_heap()\n");
	len = build_max_heap(heap, len);
	disp_heap(heap, len);
	disp_heap_order(heap, len);
		
	printf("Increase_key()\n");
	increase_key(heap, len, 8, 10);
	disp_heap_order(heap, len);

	printf("Insert()\n");
	thread_info_t elm;
	elm.id = i;
	elm.level = 5;
	strcpy(elm.describe, "Insert");
	len = insert(heap, len, &elm);
	disp_heap_order(heap, len);
	
	heap_sort(heap, len);
	printf("heap_sort()\n");	
	disp_heap(heap, len);

	printf("build_max_heap()\n");
	len = build_max_heap(heap, len);
	disp_heap(heap, len);
	disp_heap_order(heap, len);

	return 0;
}


int disp_heap(thread_info_t heap[], int len)
{
	printf("----------START-------------\n");
	printf("index\tid\tlevel\tdescribe\n");
	int i;
	for(i = 0; i < len; i++)
	{
		printf("%3d:\t%3d\t%1d\t%s\n", i,heap[i].id, heap[i].level, heap[i].describe);
	}
	printf("------------END-------------\n");
}

int build_max_heap(thread_info_t heap[], int len)
{
	int i;
	for(i = len/2; i > 0; i--)
	{
		max_heapify(heap, len, i - 1);
	}
	return len;
}

int max_heapify(thread_info_t heap[], int len, int index)
{
	int left = LEFT(index);
	int right = RIGHT(index);
	int large_i = index;
	if(left < len && heap[left].level > heap[large_i].level)
	{
		large_i = left;
	}
	
	if(right < len && heap[right].level > heap[large_i].level)
	{
		large_i = right;
	}

	if(large_i != index)
	{
		swap(&heap[large_i], &heap[index]);
		max_heapify(heap, len, large_i);
	}

	return large_i;
}

thread_info_t* maximum(thread_info_t heap[], int len)
{
	if(len > 0)
	{
		return &heap[0];
	}
	else
	{
		fprintf(stderr,"%d:ERROR:len of heap is no more than 0\n", __LINE__);
		return NULL;
	}
	
}


int extract_max(thread_info_t heap[], int len, thread_info_t *elm)
{
	thread_info_t *val = maximum(heap, len);
	if(NULL == val)
	{
		return -1;
	}
	
	memcpy(elm, val, sizeof(thread_info_t));

	len--;
	heap[0] = heap[len];
	max_heapify(heap, len, 0);
	return len;
}

int insert(thread_info_t heap[], int len, thread_info_t *elm)
{
	if(len >= MAX_LEN)
	{
		fprintf(stderr, "%d:ERROR len excessed of MAX_LEN\n", __LINE__);
		return -1;
	}
	memcpy(&heap[len], elm, sizeof(thread_info_t));
	len++;
	increase_key(heap, len, len - 1, elm->level);
	return len;
}

int increase_key(thread_info_t heap[], int len, int index, int key)
{
	if(index >= len || key < heap[index].level)
	{
		return -1;
		fprintf(stderr, "%d:ERROR\n", __LINE__);
	}
	heap[index].level = key;
	int parent = PARENT(index);
	while(index > 0 && heap[parent].level < heap[index].level)
	{
		swap(&heap[parent], &heap[index]);
		index = parent;
		parent = PARENT(index);
	}
}

int heap_sort(thread_info_t heap[], int len)
{
	int i = len - 1;
	for(i; i > 0; i--)
	{
		swap(&heap[0], &heap[i]);
		max_heapify(heap, i, 0);	
	}
}


int swap(thread_info_t *x, thread_info_t *y)
{
	thread_info_t tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;

	return 0;
}

int disp_heap_order(thread_info_t heap_org[], int len)
{
	if(len <= 0)
	{
		return 0;
	}
	thread_info_t *heap = malloc(len*sizeof(thread_info_t));
	memcpy(heap, heap_org, len*sizeof(thread_info_t));
	thread_info_t elm;
	printf("-----------ORDER_START------------\n");
	printf("index\tid\tlevel\tdescribe\n");
	int i = 0;
	while(len)
	{
		extract_max(heap, len, &elm);
		len--;
		printf("%3d\t%3d\t%1d\t%s\n", i++, elm.id, elm.level, elm.describe);
	}
	printf("------------ORDER_END-----------\n");
	free(heap);
	return len;
}
