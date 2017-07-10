#include <stdio.h>

int main(int argc, char **argv)
{
	#ifdef __MMX__
	printf("MMX instruction set enabled\n");
#endif

#ifdef __SSE__
	printf("SSE instruction set enabled\n");
#endif
#ifdef __SSE2__
	printf("SSE2 instruction set enabled\n");
#endif
#ifdef __SSE3__
	printf("SSE3 instruction set enabled\n");
#endif
#ifdef __SSE4_2__
	printf("SSE4.2 instruction set enabled\n");
#endif
	return 0;
}
