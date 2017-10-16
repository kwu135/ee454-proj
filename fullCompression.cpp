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

void unquantizateDct(int** dct, int quantizationTable[N][N]) {
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
	jpeg.push_back(0x44);
	jpeg.push_back(0x00);
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


	unsigned char grayscaleArray[SIZE][SIZE]; 
	readGSBMP("elephant.bmp", grayscaleArray);


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

		/**{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}**/
	};

	int h;
	int w;
	for (h = 0; h <= height - 8; h += 8) {
		for (w = 0; w <= width - 8; w += 8) {
			double** pixels = new double*[N];
			for (int i = 0; i < N; i++) {
				pixels[i] = new double[N];
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels[i][j] = ((double)grayscaleArray[h+i][w+j])-128;
				}
			}

			int** dct = generateDct(pixels, cosine, coefficient);
			quantizateDct(dct, quantizationTable);

			vector<bool> encode = HuffmanEncode(dct);
			if(h == 24*8 && w == 19* 8) {
				for(int dctY = 0; dctY < N; dctY++) {
					for(int dctX = 0; dctX < N; dctX++) {
						//cout << dct[dctY][dctX] << " ";
					}
					//cout << endl;
				}
				//cout << endl;
				for(int m = 0; m < encode.size(); m++) {
					cout << (int)encode[m];
				}
				cout << endl << endl;
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
						cout << pixels2[i][j] << "   ";
					}
				}
				if(h == 24*8 && w == 19* 8)
					cout << endl;
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
	
	ofstream file("file.jpg");
	for(int i = 0; i < jpeg.size(); i++)
	{
		file << jpeg[i];
	}
	file.close();

	showGSBMP(grayscaleArray);
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
