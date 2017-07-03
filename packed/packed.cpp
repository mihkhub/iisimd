/* SSE2: load,addition and store */
#include <immintrin.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	double a[2] = {3.14, 0.618};
	double b[2] = {0.0, 0.0};
	__m128d t = _mm_load_pd(a);
	t = t + 3;
	_mm_store_pd(b, t);
	printf("b0=%lf\n", b[0]);
	return 0;
}
