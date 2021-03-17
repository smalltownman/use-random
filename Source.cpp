#define _CRT_SECURE_NO_WARNINGS
#include <random>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char gnuplot[] = "\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist";

std::random_device rd;
std::mt19937 mersenne(rd());
double MK(int N) {
	int k = 0;
	for (int i = 0; i < N; i++) {
		double x = (double)mersenne() / 4294967296.0L;
		double y = (double)mersenne() / 4294967296.0L;
		double z = (double)mersenne() / 4294967296.0L;
		if (x *x + y *y + z*z - 1.0 < 1e-14) {
			k++;
		}
	}
	return (double)k /  N;
}
int main() {
	double S = 0.0, x = 0.0;
	int N[5] = { 100, 1000, 10000, 100000, 1000000 };

	FILE * f = fopen("one.txt", "w");
	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 100; j++) {
			S = MK(N[i]);
			fprintf(f, "%d\t%lg\n", N[i], fabs(S - M_PI / 6.0));
		}

	}

	fclose(f);


#pragma region drawing a graph

	FILE * pipe = _popen(gnuplot, "w");
	fprintf(pipe,
		"set terminal postscript eps enhanced\n"
		"set terminal pngcairo size 40cm, 20cm font \'Times, 10\'\n"

		"set output \'curve1.png\'\n"

		"set grid lw 1\n"

		"set format x \"10^{%%L}\"\n"
		"set log x\n"
		"set autoscale x\n"
		"set format y \"10^{%%L}\"\n"
		"set log y\n"
		"set autoscale y\n"

	
		"plot	\'one.txt\' using 1:2 notitle  w p lc rgb\'#008072\'\n");
	_pclose(pipe);

#pragma endregion

	return 0;
}