#include "bmplib.h"
#include "Huffman.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

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

void quantizateDct(int** dct, int quantizationTable[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] = round(dct[i][j] / quantizationTable[i][j]);
		}
	}
}

void quantizateDct(float** dct, int quantizationTable[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] = round(dct[i][j] / quantizationTable[i][j]);
		}
	}
}

void unquantizateDct(int** dct, int quantizationTable[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] *= quantizationTable[i][j];
		}
	}
}

int** AlternativeDct(double** pixels, int quantizationTable[N][N]) {
	const float coeff[7] = {
		0.49039, 0.46194, 0.41573, 0.35355,
		0.27779, 0.19134, 0.09755
	};
	float** tmp = new float*[N];
	int** quant = new int*[N];
	for(int i = 0; i < N; i++) {
		tmp[i] = new float[N];
		quant[i] = new int[N];
		float s0 = (float) (pixels[i][0] + pixels[i][7]) - 256;
		float s1 = (float) (pixels[i][1] + pixels[i][6]) - 256;
		float s2 = (float) (pixels[i][2] + pixels[i][5]) - 256;
		float s3 = (float) (pixels[i][3] + pixels[i][4]) - 256;

		float d0 = (float) (pixels[i][0] - pixels[i][7]);
		float d1 = (float) (pixels[i][1] - pixels[i][6]);
		float d2 = (float) (pixels[i][2] - pixels[i][5]);
		float d3 = (float) (pixels[i][3] - pixels[i][4]);

		tmp[i][ 0]     = coeff[3]*(s0+s1+s2+s3);
		tmp[i][1] = coeff[0]*d0+coeff[2]*d1+coeff[4]*d2+coeff[6]*d3;
		tmp[i][2] = coeff[1]*(s0-s3)+coeff[5]*(s1-s2);
		tmp[i][3] = coeff[2]*d0-coeff[6]*d1-coeff[0]*d2-coeff[4]*d3;
		tmp[i][4] = coeff[3]*(s0-s1-s2+s3);
		tmp[i][5] = coeff[4]*d0-coeff[0]*d1+coeff[6]*d2+coeff[2]*d3;
		tmp[i][6] = coeff[5]*(s0-s3)+coeff[1]*(s2-s1);
		tmp[i][7] = coeff[6]*d0-coeff[4]*d1+coeff[2]*d2-coeff[0]*d3;
	}
	for (int col = 0; col < 8; col++) {
		float s0 = tmp[0][col] + tmp[7][col];
		float s1 = tmp[1][col] + tmp[6][col];
		float s2 = tmp[2][col] + tmp[5][col];
		float s3 = tmp[3][col] + tmp[4][col];

		float d0 = tmp[0][col] - tmp[7][col];
		float d1 = tmp[1][col] - tmp[6][col];
		float d2 = tmp[2][col] - tmp[5][col];
		float d3 = tmp[3][col] - tmp[4][col];

		tmp[0][col] = coeff[3]*(s0+s1+s2+s3);
		tmp[1][col] = coeff[0]*d0+coeff[2]*d1+coeff[4]*d2+coeff[6]*d3;
		tmp[2][col] = coeff[1]*(s0-s3)+coeff[5]*(s1-s2);
		tmp[3][col] = coeff[2]*d0-coeff[6]*d1-coeff[0]*d2-coeff[4]*d3;
		tmp[4][col] = coeff[3]*(s0-s1-s2+s3);
		tmp[5][col] = coeff[4]*d0-coeff[0]*d1+coeff[6]*d2+coeff[2]*d3;
		tmp[6][col] = coeff[5]*(s0-s3)+coeff[1]*(s2-s1);
		tmp[7][col] = coeff[6]*d0-coeff[4]*d1+coeff[2]*d2-coeff[0]*d3;
	}
	quantizateDct(tmp,quantizationTable);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			quant[i][j] = (int)tmp[i][j];
		}
		delete[] tmp[i];
	}
	delete[] tmp;
	return quant;
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

vector<unsigned char> ConvertBitsToBytes(vector<bool> bits)
{
	vector<unsigned char> bytes;
	for(int i = 0; i < bits.size(); i = i + 8)
	{
		int endBit = i + 7;
		if(endBit >= bits.size()){
			endBit = bits.size() - 1;
		}
		unsigned char newByte = 0;
		for(unsigned int j = 0; j < 8; j++)
		{
			if(i + j >= bits.size()) {
				newByte = newByte ^ (1 << (7 -j));
			}
			else {
				newByte = newByte ^ (bits[i+j] << (7 - j));
			}
		}
		bytes.push_back(newByte);
		if(newByte == 0xFF) {
			bytes.push_back(0x00);
		}
	}
	return bytes;
}

vector<unsigned char> CreateJPEGVector(vector<unsigned char> quant, vector<unsigned char> bytes) {
	vector<unsigned char> jpeg;
	//File Start
	jpeg.push_back(0xFF);
	jpeg.push_back(0xD8);
	//APP0
	jpeg.push_back(0xff);
	jpeg.push_back(0xe0);
	jpeg.push_back(0x00);
	jpeg.push_back(0x10);
	jpeg.push_back(0x4a);
	jpeg.push_back(0x46);
	jpeg.push_back(0x49);
	jpeg.push_back(0x46);
	jpeg.push_back(0x00);
	jpeg.push_back(0x01);
	jpeg.push_back(0x01);
	jpeg.push_back(0x00);
	jpeg.push_back(0x00);
	jpeg.push_back(0x01);
	jpeg.push_back(0x00);
	jpeg.push_back(0x01);
	jpeg.push_back(0x00);
	jpeg.push_back(0x00);
	//Quant
	jpeg.insert(jpeg.end(), quant.begin(), quant.end());
	//Info
	jpeg.push_back(0xff);
	jpeg.push_back(0xc0);
	jpeg.push_back(0x00);
	jpeg.push_back(0x0B);
	jpeg.push_back(0x08);
	jpeg.push_back(0x01);
	jpeg.push_back(0x00);
	jpeg.push_back(0x01);
	jpeg.push_back(0x00);
	jpeg.push_back(0x01);
	jpeg.push_back(0x01);
	jpeg.push_back(0x11);
	jpeg.push_back(0x00);
	//Restart
	/**jpeg.push_back(0xff);
	jpeg.push_back(0xdd);
	jpeg.push_back(0x00);
	jpeg.push_back(0x04);
	jpeg.push_back(0x00);
	jpeg.push_back(0x04);**/

	//Lum Huffman DC
	vector<unsigned char> huffmanDC = GetHuffmanDC();
	jpeg.insert(jpeg.end(), huffmanDC.begin(), huffmanDC.end());
	//Lum Huffman AC
	vector<unsigned char> huffmanAC = GetHuffmanAC();
	jpeg.insert(jpeg.end(), huffmanAC.begin(), huffmanAC.end());

	//Image
	jpeg.push_back(0xFF);
	jpeg.push_back(0xDA);
	jpeg.push_back(0x00);
	jpeg.push_back(0x08);
	jpeg.push_back(0x01);
	jpeg.push_back(0x01);
	jpeg.push_back(0x00);
	jpeg.push_back(0x00);
	jpeg.push_back(0x3f);
	jpeg.push_back(0x00);
	jpeg.insert(jpeg.end(), bytes.begin(), bytes.end());
	jpeg.push_back(0xFF);
	jpeg.push_back(0xD9);		
	return jpeg;
}

int main(int argc, char** argv) {
	if(argc < 3)
	{
		cout << "Arguements: fullCompression [input] [output]" << endl;
		return 0;
	}


	unsigned char grayscaleArray[SIZE][SIZE]; 
	readGSBMP(argv[1], grayscaleArray);


	int width = 256; 
	int height = 256; 

	double** cosine = generateCosines();
	double** coefficient = generateCoefficients();

	vector<bool> huffmanEncode;	

	int quantizationTable[8][8] = {

		{3, 5, 7, 9, 11, 13, 15, 17},
		{5, 7, 9, 11, 13, 15, 17, 19},
		{7, 9, 11, 13, 15, 17, 19, 21},
		{9, 11, 13, 15, 17, 19, 21, 23},
		{11, 13, 15, 17, 19, 21, 23, 25},
		{13, 15, 17, 19, 21, 23, 25, 27},
		{15, 17, 19, 21, 23, 25, 27, 29},
		{17, 19, 21, 23, 25, 27, 29, 31}

		/**{16, 11, 10, 16, 24, 40, 51, 61},
		{12, 12, 14, 19, 26, 58, 60, 55},
		{14, 13, 16, 24, 40, 57, 69, 56},
		{14, 17, 22, 29, 51, 87, 80, 62},
		{18, 22, 37, 56, 68, 109, 103, 77},
		{24, 35, 55, 64, 81, 104, 113, 92},
		{49, 64, 78, 87, 103, 121, 120, 101},
		{72, 92, 95, 98, 112, 100, 103, 99}**/

		/**{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}**/
	};
	
	/**
	int fixedNum[N][N] = {
		{217,  -1,  -2, -82, -61, -24,  11,  11},
		{-70, -16, -13, -11,  12,  29,  36,  12},
		{-24,   8,  -8, -11,  -2,  21,   0,  -6},
		{  0, -20, -21, -23,  -9,   7,   0,   2},
		{ -3,   0,  18,  -3,  -4,   1,   2,   0},
		{ -2,   0,   0,  -3,   4,   2,  -3,  -1},
		{ -3,   1,   4,  -2,   0,   3,  -3,   0},
		{ -2,   2,   0,  -2,   3,   0,   0,   1}

	};
	int** fixed = new int*[N];
	for(int f = 0; f < N; f++) {
		fixed[f] = new int[N];
		for(int d = 0; d < N; d++) {
			fixed[f][d] = fixedNum[f][d];
		}
	}**/

	int h;
	int w;
	int previousDC;
	for (h = 0; h <= height - 8; h += 8) {
		for (w = 0; w <= width - 8; w += 8) {
			double** pixels = new double*[N];
			for (int i = 0; i < N; i++) {
				pixels[i] = new double[N];
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels[i][j] = ((double)grayscaleArray[h+i][w+j]);
				}
			}

			int** dct = generateDct(pixels, cosine, coefficient);
			quantizateDct(dct, quantizationTable);
			/**if(h == 0 && w == 0)
			{
				previousDC = dct[0][0];
			}
			else
			{
				int saveDC = dct[0][0];
				dct[0][0] -= previousDC;
				previousDC = saveDC;
			}
			vector<bool> encode = HuffmanEncode(dct);**/
			int** alternativeDCT = AlternativeDct(pixels, quantizationTable);
			if(h == 0 && w == 0)
			{
				previousDC = alternativeDCT[0][0];
			}
			else
			{
				int saveDC = alternativeDCT[0][0];
				alternativeDCT[0][0] -= previousDC;
				previousDC = saveDC;
			}
			vector<bool> encode = HuffmanEncode(alternativeDCT);
			
			if(h == 5*8 && w == 19* 8) {
				for(int dctY = 0; dctY < N; dctY++) {
					for(int dctX = 0; dctX < N; dctX++) {
						//cout << dct[dctY][dctX] << " ";
					}
					//cout << endl;
				}
				//cout << endl;
				for(int m = 0; m < encode.size(); m++) {
					//cout << (int)encode[m];
				}
				//cout << endl << endl;
			}
			huffmanEncode.insert(huffmanEncode.end(), encode.begin(), encode.end());

			unquantizateDct(dct, quantizationTable);
			double** pixels2 = generatePixels(dct, cosine, coefficient);
			

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels2[i][j] = round(pixels2[i][j] + 128);
					if (pixels2[i][j] > 255) {
						pixels2[i][j] = 255;
					}
					if (pixels2[i][j] < 0) {
						pixels2[i][j] = 0;
					}
					grayscaleArray[i+h][w+j] = (unsigned char)pixels2[i][j];
					if(h == 24*8 && w == 19* 8)
					{
						//cout << pixels2[i][j] << "   ";
					}
				}
				//if(h == 24*8 && w == 19* 8)
					//cout << endl;
			}

			for (int i = 0; i < N; i++) {
				delete pixels[i];
				delete dct[i];
			}
			delete pixels;
			delete dct;
		}
	}
	
	/**
	for(int i = 0; i < huffmanEncode.size(); i++)
	{
		if(huffmanEncode[i])
			cout << "1";
		else
			cout << "0";
	}
	cout << endl;**/

	vector<unsigned char> bytes = ConvertBitsToBytes(huffmanEncode);
	vector<unsigned char> quantHeader = ConvertQuantizationHeader(quantizationTable);

	// for (;h < height; h++) {
	// 	for (w=0;w < width; w++) {
	// 		img(w,h,0,0) = 0;
	// 		img(w,h,0,1) = 0;
	// 		img(w,h,0,2) = 0;
	// 	}
	// }
	vector<unsigned char> jpeg = CreateJPEGVector(quantHeader, bytes);
	
	ofstream file(argv[2]);
	for(int i = 0; i < jpeg.size(); i++)
	{
		file << jpeg[i];
	}
	file.close();

	//showGSBMP(grayscaleArray);
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
