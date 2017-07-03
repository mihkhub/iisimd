/********************************************************************************

 *Joseph D. Wieber, Jr. *

 *Gary M. Zoppetti *

 * *
 *Source used to test performance of some intrinsics functions *

 ********************************************************************************/

#include "iostream"

#include "iomanip"

#include "cstdlib"

#include "ctime"

#include <immintrin.h>
#include <inttypes.h>

using namespace std;

/********************************************************************************

 * DECLARATIONS *

 ********************************************************************************/

void dotmul_naive(short A[], short B[], short &C, const int SIZE);

void dotmul_intrins1(short A[], short B[], short &C, const int SIZE);

void dotmul_intrins2(short A[], short B[], short &C, const int SIZE);

void dotmul_intrins3(short A[], short B[], short &C, const int SIZE);

void dotmul_intrins4(short A[], short B[], short &C, const int SIZE);

void print_matrix(short A[], const int SIZE);

void fill_matrices(short A[], short B[], const int SIZE);

/********************************************************************************

 * GLOBALS *

 ********************************************************************************/

const int MAX = 1e+8;

short A[MAX], B[MAX];

/********************************************************************************

 * MAIN *

 *******************************************************************************/

int

main(int argc, char *argv[])

{

	int i;

	int SIZE;

	short C(0), D(0);

	if (argc != 2)

	{

		cout << "Usage: " << argv[0] << " <size>" << endl;

		exit(-1);

	}

	SIZE = atoi(argv[1]);

	if

	(SIZE % 4 != 0)

	{

		cout << "SIZE must be a multiple of 4." << endl;

		exit(-2);

	}

//one fill many multiplies

	fill_matrices(A, B, SIZE);

	time_t start = clock();

	dotmul_naive(A, B, D, SIZE);

	time_t end = clock();

	double elap = double(end - start) / CLOCKS_PER_SEC;

	cout << "For a vector of " << SIZE << " shorts, dotmul_naive Time = "

	<< setprecision(4) << elap << "s." << endl;

	cout << "*****************************************************************";

////////////////////////////////////////////////////////////////////////

	start = clock();

	dotmul_intrins1(A, B, C, SIZE);

	end = clock();

	double elap1 = double(end - start) / CLOCKS_PER_SEC;

	cout << "For a vector of " << SIZE << " shorts, dotmul_intrins1 time = "

	<< setprecision(4) << elap1 << "s." << endl;

	cout << "Speedup ==> " << elap / elap1 << endl;

	if (C != D)

	{

		cout << "intrins1 yields a different result naive result: " << D

		<< "intrins1 result: " << C << endl;

	}

	else

		cout << "Results for intrins1 verified";

	cout << "*****************************************************************";

////////////////////////////////////////////////////////////////////////

	start = clock();

	dotmul_intrins2(A, B, C, SIZE);

	end = clock();

	double elap2 = double(end - start) / CLOCKS_PER_SEC;

	cout << "For a vector of " << SIZE << " shorts, dotmul_intrins2 time = "

	<< setprecision(4) << elap2 << "s." << endl;

	cout << "Speedup ==> " << elap / elap2 << endl;

	if (C != D)

	{

		cout << "intrins2 yields a different result naive result: " << D

		<< "intrins2 result: " << C << endl;

	}

	else

		cout << "Results for intrins2 verified";

	cout << "*****************************************************************";

////////////////////////////////////////////////////////////////////////

	start = clock();

	dotmul_intrins3(A, B, C, SIZE);

	end = clock();

	double elap3 = double(end - start) / CLOCKS_PER_SEC;

	cout << "For a vector of " << SIZE << " shorts, dotmul_intrins3 time = "

	<< setprecision(4) << elap3 << "s." << endl;

	cout << "Speedup ==> " << elap / elap3 << endl;

	if (C != D)

	{

		cout << "intrins3 yields a different result naive result: " << D

		<< "intrins3 result: " << C << endl;

	}

	else

		cout << "Results for intrins3 verified";

	cout << "*****************************************************************";

////////////////////////////////////////////////////////////////////////

	start = clock();

	dotmul_intrins4(A, B, C, SIZE);

	end = clock();

	double elap4 = double(end - start) / CLOCKS_PER_SEC;

	cout << "For a vector of " << SIZE << " shorts, dotmul_intrins4 time = "

	<< setprecision

	(4) << elap4 << "s." << endl;

	cout << "Speedup ==> " << elap / elap4 << endl;

	if (C != D)

	{

		cout << "intrins4 yields a different result naive result: " << D

		<< "intrins4 result: " << C << endl;

	}

	else

		cout << "Results for intrins4 verified";

	cout << "*****************************************************************";

	return (0);

}

/********************************************************************************

 * DEFINITIONS *

 ********************************************************************************/

void

dotmul_naive(short A[], short B[], short &C, const int SIZE)

{

	register int k;

	C = 0;

	for (k = 0; k < SIZE; k++)

		C += A[k] * B[k];

}

/********************************************************************************/

/*void

dotmul_intrins1(short A[], short B[], short &C, const int SIZE)

{

	register int k;

	short sarr[4];

	register int64_t a, b;

	register __m64 catch_mul, part_sum;

	catch_mul;

	part_sum;

	for (k = 0; k < SIZE; k += 4)

	{

		a = __ld8_acq((void*) &A[k]);

		b = __ld8_acq((void*) &B[k]);

		catch_mul = _m64_pmpyshr2(_m_from_int64(a), _m_from_int64(b), 0);

		part_sum = _m_paddw(part_sum, catch_mul);

	}

	__st8_rel(&sarr[0], _m_to_int64(part_sum));

	C = sarr[0] + sarr[1] + sarr[2] + sarr[3];

}*/

/********************************************************************************/

void

dotmul_intrins2(short A[], short B[], short &C, const int SIZE)

{

	register int k;

	short sarr[4];

	register __m64 *a_ptr, *b_ptr, catch_mul, part_sum;

	catch_mul;

	part_sum;

	for (k = 0; k < SIZE; k += 4)

	{

		a_ptr = (__m64 *) &A[k];

		b_ptr = (__m64 *) &B[k];

		catch_mul = _m64_pmpyshr2(*a_ptr, *b_ptr, 0);

		part_sum = _m_paddw(part_sum, catch_mul);

	}

	__st8_rel(&sarr[0], _m_to_int64(part_sum));

	C = sarr[0] + sarr[1] + sarr[2] + sarr[3];

}

/********************************************************************************/

void

dotmul_intrins3(short A[], short B[], short &C, const int SIZE)

{

	register int k;

	register __int64 sum;

	register __m64 *a_ptr, *b_ptr, catch_mul(0), part_sum(0);

	for (k = 0; k < SIZE; k += 4)

	{

		a_ptr = (__m64 *) &A[k];

		b_ptr = (__m64 *) &B[k];

		catch_mul = _m64_pmpyshr2(*a_ptr, *b_ptr, 0);

		part_sum = _m_paddw(part_sum, catch_mul);

	}

	sum = _m64_extr(_m_to_int64(part_sum), 0, 16)

	+ _m64_extr(_m_to_int64(part_sum), 16, 16)

	+ _m64_extr(_m_to_int64(part_sum), 32, 16)

	+ _m64_extr(_m_to_int64(part_sum), 48, 16);

	C = (short) _m_to_int(_m_from_int64(sum));

}

/********************************************************************************/

void

dotmul_intrins4(short A[], short B[], short &C, const int SIZE)

{

	union

	{

		__m64 part_sum;

		short part[4];

	} s;

	register int k;

	register __m64 *a_ptr, *b_ptr, catch_mul(0);

	for (k = 0; k < SIZE; k += 4)

	{

		a_ptr = (__m64 *) &A[k];

		b_ptr = (__m64 *) &B[k];

		catch_mul = _m64_pmpyshr2(*a_ptr, *b_ptr, 0);

		s.part_sum = _m_paddw(s.part_sum, catch_mul);

	}

	C = s.part[0] + s.part[1] + s.part[2] + s.part[3];

}

/********************************************************************************/

void

fill_matrices(short A[], short B[], const int SIZE)

{

	int i;

	int r1, r2;

	srand(0); // keep it consistent for testing

	for (i = 0; i < SIZE; i++)

	{

		A[i] = rand() % 9 + 1;

		B[i] = rand() % 9 + 1;

	}

}

/********************************************************************************/

void

print_matrix(short A[], const int SIZE)

{

	int i;

	for (i = 0; i < SIZE; i++)

	{

		cout << setw(10) << A[i];

	}

	cout << endl;

	cout << endl;

}

/********************************************************************************/
