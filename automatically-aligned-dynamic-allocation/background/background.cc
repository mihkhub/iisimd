/*
 * class-specific allocation and deallocation functions
 * */
#include <stdio.h>
#include <mm_malloc.h>
class __attribute__((aligned(64) )) X
{
	double elem[8];
public:
	void *operator new(size_t size)
	{
		return _mm_malloc(size, alignof(X));
	}
	void operator delete(void *p)
	{
		return _mm_free(p);
	}
};
int main(int argc, char **argv)
{
	X *hx = new X;
	printf("Heap hx=%p\n",hx);
	X sx;
	printf("Stack sx=%p\n",&sx);
	free(hx);
	return 0;
}
