/* PSHUFB 64-bit operands */
/* right to left: */
#include <stdio.h>
#include <immintrin.h>
#include <inttypes.h>

void print_arr(uint32_t *arr, size_t len)
{
	printf("\n");
	for(size_t i =0; i < len; ++i)
	{
		printf("array[%zu]=%#x\n",i, arr[i]);
	}
	printf("\n");
}
int main(int argc, char **argv)
{
	uint32_t as[2] = {0xa1b2c3d4,0x1a2b3c4d};
	int64_t output= 0;
	print_arr(as, 2);
	/* Set packed 32-bit integers in dst with the supplied values. */
	__m64 a = _mm_set_pi32(as[1], as[0]);
	__m64 b = _mm_set_pi8(4,5,6,7,0,1,2,3);
	__m64 c =  _mm_shuffle_pi8(a, b);
	output = _mm_cvtm64_si64(c);
	printf("output=%#lx\n", output);
	return 0;
}
