#include "CImg.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cimg_library;

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

int** generateDct(double** pixels, double** cosine, double** coefficient) {
	int** dct = new int*[N];
	for (int i = 0; i < N; i++) {
		dct[i] = new int[N];
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

void quantizateDct(int** dct, double quantizationTable[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] = round(dct[i][j] / quantizationTable[i][j]);
		}
	}
}

void unquantizateDct(int** dct, double quantizationTable[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] *= quantizationTable[i][j];
		}
	}
}

// Inverse DCT
double** generatePixels(int** dct, double** cosine, double** coefficient) {
	double** pixels = new double*[N];
	for (int i = 0; i < N; i++) {
		pixels[i] = new double[N];
	}	

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			double temp = 0.0;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					temp += cosine[x][i] * cosine[y][j] * dct[i][j] * coefficient[i][j];
				}
			}
			temp *= 1 / sqrt(2 * N);
			pixels[x][y] = temp;
		}
	}

	return pixels;	
}

int** getGrayscale(CImg<unsigned char> img1) {
	int width = img1.width();
	int height = img1.height();

	int **grayscaleArray;

	grayscaleArray = new int*[height];
	for (int i = 0; i < height; ++i) {
		grayscaleArray[i] = new int[width];
	}

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			grayscaleArray[r][c] = (int)(0.299*img1(c,r,0,0) + 0.587*img1(c,r,0,1) + 0.114*img1(c,r,0,2));
		}
	}

	return grayscaleArray;
}

void print2DArray(double** arr) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void print2DArray(int** arr) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv) {
	CImg<unsigned char> img;

	img.load_jpeg("input.jpg");

	int **grayscaleArray = getGrayscale(img);

	// CImgDisplay main_disp(img,"Image");
	// while (!main_disp.is_closed()) {
 //    	main_disp.wait();
	// }

	int width = img.width();
	int height = img.height();

	double** cosine = generateCosines();
	double** coefficient = generateCoefficients();

	double quantizationTable[8][8] = {
		{3, 5, 7, 9, 11, 13, 15, 17},
		{5, 7, 9, 11, 13, 15, 17, 19},
		{7, 9, 11, 13, 15, 17, 19, 21},
		{9, 11, 13, 15, 17, 19, 21, 23},
		{11, 13, 15, 17, 19, 21, 23, 25},
		{13, 15, 17, 19, 21, 23, 25, 27},
		{15, 17, 19, 21, 23, 25, 27, 29},
		{17, 19, 21, 23, 25, 27, 29, 31}
	};

	int h;
	int w;
	for (h = 0; h < height - 8; h += 8) {
		for (w = 0; w < width - 8; w += 8) {
			double** pixels = new double*[N];
			for (int i = 0; i < N; i++) {
				pixels[i] = new double[N];
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels[i][j] = grayscaleArray[h+i][w+j]-128;
				}
			}

			int** dct = generateDct(pixels, cosine, coefficient);
			quantizateDct(dct, quantizationTable);

			unquantizateDct(dct, quantizationTable);
			double** pixels2 = generatePixels(dct, cosine, coefficient);

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels2[i][j] = round(pixels2[i][j] + 128);
					if (pixels2[i][j] > 255) {
						pixels2[i][j] = 255;
					}
				
					img(w+j,h+i,0,0) = pixels2[i][j];
					img(w+j,h+i,0,1) = pixels2[i][j];
					img(w+j,h+i,0,2) = pixels2[i][j];
				}
			}

			for (int i = 0; i < N; i++) {
				delete pixels[i];
				delete pixels2[i];
				delete dct[i];
			}
			delete pixels;
			delete pixels2;
			delete dct;
		}
	}

	// for (;h < height; h++) {
	// 	for (w=0;w < width; w++) {
	// 		img(w,h,0,0) = 0;
	// 		img(w,h,0,1) = 0;
	// 		img(w,h,0,2) = 0;
	// 	}
	// }

	CImgDisplay main_disp(img,"Click a point");
	while (!main_disp.is_closed()) {
    	main_disp.wait();
	}

	// double x[8][8] = {
	// 	{140, 144, 147, 140, 140, 155, 179, 175},
	// 	{144, 152, 140, 147, 140, 148, 167, 179},
	// 	{152, 155, 136, 167, 163, 162, 152, 172},
	// 	{168, 145, 156, 160, 152, 155, 136, 160},
	// 	{162, 148, 156, 148, 140, 136, 147, 162},
	// 	{147, 167, 140, 155, 155, 140, 136, 162},
	// 	{136, 156, 123, 167, 162, 144, 140, 147},
	// 	{148, 155, 136, 155, 152, 147, 147, 136}
	// };
}