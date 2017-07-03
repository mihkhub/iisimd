#include <mm_malloc.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int *p = (int*)_mm_malloc(1024, 64);
	printf("p=%p\n",p);
	_mm_free(p);
	return 0;
}
