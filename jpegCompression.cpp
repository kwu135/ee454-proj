#include <iostream>
#include <math.h>

using namespace std;

const int N = 8;

double** generateCosines() {
	double** cosine = new double*[N];
	for (int i = 0; i < N; i++) {
		cosine[i] = new double[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cosine[i][j] = cos(((2*i+1)*j*M_PI)/(2*N));
		}
	}

	return cosine;
}

double** generateCoefficients() {
	double** coefficient = new double*[N];
	for (int i = 0; i < N; i++) {
		coefficient[i] = new double[N];
	}
	double invSqrt2 = 1/sqrt(2);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			coefficient[i][j] = 1;
			if (i == 0) {
				coefficient[i][j] *= invSqrt2;
			}
			if (j == 0) {
				coefficient[i][j] *= invSqrt2;
			}
		}
	}

	return coefficient;
}

double** generateDct(double** pixels, double** cosine, double** coefficient) {
	double** dct = new double*[N];
	for (int i = 0; i < N; i++) {
		dct[i] = new double[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			double temp = 0.0;
			for (int x = 0; x < N; x++) {
				for (int y = 0; y < N; y++) {
					temp += cosine[x][i] * cosine[y][j] * pixels[x][y];
				}
			}
			temp *= coefficient[i][j] / sqrt(2 * N);
			dct[i][j] = round(temp);
		}
	}

	return dct;
}

void print2DArray(double** arr) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv) {
	int N = 8;
	double** cosine = generateCosines();
	double** coefficient = generateCoefficients();

	double x[8][8] = {
		{140, 144, 147, 140, 140, 155, 179, 175},
		{144, 152, 140, 147, 140, 148, 167, 179},
		{152, 155, 136, 167, 163, 162, 152, 172},
		{168, 145, 156, 160, 152, 155, 136, 160},
		{162, 148, 156, 148, 140, 136, 147, 162},
		{147, 167, 140, 155, 155, 140, 136, 162},
		{136, 156, 123, 167, 162, 144, 140, 147},
		{148, 155, 136, 155, 152, 147, 147, 136}
	};

	double** pixels = new double*[N];
	for (int i = 0; i < N; i++) {
		pixels[i] = new double[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			pixels[i][j] = x[i][j]-128;
		}
	}

	double** gct = generateDct(pixels, cosine, coefficient);
	print2DArray(gct);
}