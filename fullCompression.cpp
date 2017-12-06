#include "bmplib.h"
#include "Huffman.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

ofstream myfile;

struct Population
{
	vector<int**> quantizationTables;
};


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

int** generateRandomQuantizationTable()
{
	int** randomQuantizationTable = new int*[N];

	for (int i = 0; i < N; i++) {
		randomQuantizationTable[i] = new int[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			randomQuantizationTable[i][j] = rand() % 256 + 1;
		}
	}

	return randomQuantizationTable;
}


Population generateInitialRandomPopulation()
{
	Population population;

	int baseQuantizationTable[N][N] = {
		{16, 11, 10, 16, 24, 40, 51, 61},
		{12, 12, 14, 19, 26, 58, 60, 55},
		{14, 13, 16, 24, 40, 57, 69, 56},
		{14, 17, 22, 29, 51, 87, 80, 62},
		{18, 22, 37, 56, 68, 109, 103, 77},
		{24, 35, 55, 64, 81, 104, 113, 92},
		{49, 64, 78, 87, 103, 121, 120, 101},
		{72, 92, 95, 98, 112, 100, 103, 99}
	};

	for (int iter = 0; iter < 8; iter++) {
		int q = (iter + 1) * 10;
		double s; 
		if (q < 50)
		    s = 5000/q;
		else
		    s = 200 - 2*q;

		int** tempQuantizationTable = new int*[N];

		for (int i = 0; i < N; i++) {
			tempQuantizationTable[i] = new int[N];
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				tempQuantizationTable[i][j] = round((s * baseQuantizationTable[i][j] + 50) / 100);
				if (tempQuantizationTable[i][j] < 1) {
					tempQuantizationTable[i][j] = 1;
				}
			}
		}

		population.quantizationTables.push_back(tempQuantizationTable);
		// population.quantizationTables.push_back(generateRandomQuantizationTable());
	}

	return population;
}

void printPopulation(Population population)
{
	for (int i = 0; i < population.quantizationTables.size(); i++) {
		cout << "Num " << i << endl;
		print2DArray(population.quantizationTables[i]);
		cout << endl;
	}
}

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

int nonZeroCounter(int** quantizationTable) {
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (quantizationTable[i][j] != 0) {
				counter++;
			}
		}
	}
	return counter;
}

int getImageQuality(int** pixels, int** compressedPixles) {
	int counter = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			counter += pow((pixels[i][j] - compressedPixles[i][j]), 2);
		}
	}

	return counter;
}

double fitnessValue(int nonZeroCounter, int imageQuality) {
	if (imageQuality > 30000000) {
		return 2;
	}
	// cout << imageQuality << " " << nonZeroCounter << endl;
	// return (imageQuality / 30000000.0) * (nonZeroCounter / 65536.0);
	return pow((imageQuality / 30000000.0), 2) + pow((nonZeroCounter / 65536.0),2);
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
					temp += cosine[x][i] * cosine[y][j] * (pixels[x][y] - 128);
				}
			}
			temp *= coefficient[i][j] / sqrt(2 * N);
			dct[i][j] = round(temp);
		}
	}

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			myfile << dct[i][j] << " ";
		}
		myfile << endl;
	}
	return dct;
}

void quantizateDct(int** dct, int** quantizationTable) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] = round(dct[i][j] / quantizationTable[i][j]);
		}
	}
}

void quantizateDct(float** dct, int** quantizationTable) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] = round(dct[i][j] / quantizationTable[i][j]);
		}
	}
}

void unquantizateDct(int** dct, int** quantizationTable) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dct[i][j] *= quantizationTable[i][j];
		}
	}
}

int** AlternativeDct(int** pixels, int** quantizationTable) {
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

		tmp[i][0] = coeff[3]*(s0+s1+s2+s3);
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
int** generatePixels(int** dct, double** cosine, double** coefficient) {
	int** pixels = new int*[N];
	for (int i = 0; i < N; i++) {
		pixels[i] = new int[N];
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

			pixels[x][y] = round(temp + 128);
			if (pixels[x][y] > 255) {
				pixels[x][y] = 255;
			}
			if (pixels[x][y] < 0) {
				pixels[x][y] = 0;
			}
		}
	}

	return pixels;	
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

double fitnessValueFromQuantizationTable(unsigned char grayscaleArray[SIZE][SIZE], int height, int width, int** quantizationTable, double** cosine, double** coefficient) {
	int totalImageQuality = 0;
	int totalNonZeroCounter = 0;

	int** pixels = new int*[N];
	for (int i = 0; i < N; i++) {
		pixels[i] = new int[N];
	}

	for (int h = 0; h <= height - 8; h += 8) {
		for (int w = 0; w <= width - 8; w += 8) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels[i][j] = ((double)grayscaleArray[h+i][w+j]);
				}
			}

			int** alternativeDCT = AlternativeDct(pixels, quantizationTable);
			totalNonZeroCounter += nonZeroCounter(alternativeDCT);
			unquantizateDct(alternativeDCT, quantizationTable);
			int** pixels2 = generatePixels(alternativeDCT, cosine, coefficient);
			totalImageQuality += getImageQuality(pixels, pixels2);

			for (int i = 0; i < N; i++) {
				delete pixels2[i];
				delete alternativeDCT[i];
			}
			delete pixels2;
			delete alternativeDCT;
		}
	}
	
	for (int i = 0; i < N; i++) {
		delete pixels[i];
	}
	delete pixels;

	return fitnessValue(totalNonZeroCounter, totalImageQuality);
}


vector<pair<int, double> > GeneratePopulationFitness(Population p, unsigned char grayscaleArray[SIZE][SIZE], int height, int width, double** cosine, double** coefficient)
{
	vector<pair<int, double> > fitnessVector(p.quantizationTables.size());
	for (int i = 0; i < p.quantizationTables.size(); i++) {
		pair<int, double> tempPair;
		tempPair.first = i;
		tempPair.second = fitnessValueFromQuantizationTable(grayscaleArray, height, width, p.quantizationTables[i], cosine, coefficient);
		fitnessVector[i] = tempPair;
	}
	return fitnessVector;
}

vector<pair<int, int> > GenerateSelection(Population population, vector<pair<int, double> > populationFitness, mt19937& rng)
{
	sort(populationFitness.begin(),
		populationFitness.end(),
		[](pair<int, double> a, pair<int, double> b) {
			return a.second < b.second;
	});
	vector<double> probabilities(population.quantizationTables.size());
	generate(probabilities.begin(),
		probabilities.end(),
		[population]() {
		return 1.0 / population.quantizationTables.size();
	});
	probabilities[populationFitness[0].first] *= 6.0;
	probabilities[populationFitness[1].first] *= 6.0;
	for (unsigned int i = 2; i <= population.quantizationTables.size() / 2 - 1; i++)
	{
		probabilities[populationFitness[i].first] *= 3.0;
	}
	double totalProb = accumulate(probabilities.begin(), probabilities.end(), 0.0);
	transform(probabilities.begin(),
		probabilities.end(),
		probabilities.begin(),
		[totalProb](double a) {
		return a / totalProb;
	});
	vector<pair<int, int> > selection(population.quantizationTables.size());
	generate(selection.begin(),
		selection.end(),
		[probabilities, &rng]() {
		pair<int, int> parents;
		uniform_real_distribution<double> distribution(0.0, 1.0);
		double parentA = distribution(rng);
		for (unsigned int i = 0; parentA > 0; i++)
		{
			parents.first = i;
			parentA -= probabilities[i];
		}
		double parentB = distribution(rng);
		for (unsigned int i = 0; parentB > 0; i++)
		{
			parents.second = i;
			parentB -= probabilities[i];
		}
		return parents;
	});
	return selection;
}

Population GenerateCrossoverPopulation(Population initialPopulation, std::vector<std::pair<int, int> > selection)
{
	Population newPopulation;
	newPopulation.quantizationTables.resize(initialPopulation.quantizationTables.size());
	for (unsigned int i = 0; i < selection.size(); i++)
	{
		int crossoverIndex = rand() % 64;
		int** aQuant = initialPopulation.quantizationTables[selection[i].first];
		int** bQuant = initialPopulation.quantizationTables[selection[i].second];

		int** childQuant = new int*[N];

		for (int x = 0; x < N; x++) {
			childQuant[x] = new int[N];
		}

		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				if (x * N + y < crossoverIndex) {
					childQuant[x][y] = aQuant[x][y];
				} else {
					childQuant[x][y] = bQuant[x][y];
				}
				if (rand() % 100 < 10) {
					childQuant[x][y] += (rand() % 20 - 10);
					if (childQuant[x][y] < 1) {
						childQuant[x][y] = 1;
					}
				}
			}
		}

		newPopulation.quantizationTables[i] = childQuant;
	}

	for (unsigned int i = 0; i < initialPopulation.quantizationTables.size(); i++) {
		for (int j = 0; j < N; j++) {
			delete initialPopulation.quantizationTables[i][j];
		}
		delete initialPopulation.quantizationTables[i];
	}

	return newPopulation;
}

int main(int argc, char** argv) {
	if(argc < 3)
	{
		cout << "Arguements: fullCompression [input] [output]" << endl;
		return 0;
	}

	srand (time(NULL));

	mt19937 rng(time(NULL));
  	
  	myfile.open ("dct.txt");

	unsigned char grayscaleArray[SIZE][SIZE]; 
	readGSBMP(argv[1], grayscaleArray);


	int width = 256; 
	int height = 256; 

	double** cosine = generateCosines();
	double** coefficient = generateCoefficients();

  	Population p = generateInitialRandomPopulation();
	printPopulation(p);

	for (int iteration = 0; iteration < 1; iteration++) {
		vector<pair<int, double> > populationFitness = GeneratePopulationFitness(p, grayscaleArray, height, width, cosine, coefficient);
		for (int i = 0; i < populationFitness.size(); i++) {
			cout << i << ": " << populationFitness[i].first << " -- " << populationFitness[i].second << endl;
		}
		vector<pair<int, int> > selection = GenerateSelection(p, populationFitness, rng);
		// for (int i = 0; i < selection.size(); i++) {
		// 	cout << i << ": " << selection[i].first << ", " << selection[i].second << endl;
		// }
		p = GenerateCrossoverPopulation(p, selection);
		cout << iteration << endl;
	}

	printPopulation(p);

	double min_fitness_index = 0;
	double min_fitness = -1;
	for (int i = 0; i < p.quantizationTables.size(); i++) {
		double fitness = fitnessValueFromQuantizationTable(grayscaleArray, height, width, p.quantizationTables[i], cosine, coefficient);
		cout << i << ": " << fitness << endl;
		if (fitness < min_fitness || min_fitness == -1) {
			min_fitness_index = i;
			min_fitness = fitness;
		}
	}

	cout << min_fitness_index << endl;

	vector<bool> huffmanEncode;	

	// int** quantizationTable = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1}
	// };

	int** quantizationTable = p.quantizationTables[min_fitness_index]; 

	int tempquantizationTable[N][N] = {

		// {3, 5, 7, 9, 11, 13, 15, 17},
		// {5, 7, 9, 11, 13, 15, 17, 19},
		// {7, 9, 11, 13, 15, 17, 19, 21},
		// {9, 11, 13, 15, 17, 19, 21, 23},
		// {11, 13, 15, 17, 19, 21, 23, 25},
		// {13, 15, 17, 19, 21, 23, 25, 27},
		// {15, 17, 19, 21, 23, 25, 27, 29},
		// {17, 19, 21, 23, 25, 27, 29, 31}

		{16, 11, 10, 16, 24, 40, 51, 61},
		{12, 12, 14, 19, 26, 58, 60, 55},
		{14, 13, 16, 24, 40, 57, 69, 56},
		{14, 17, 22, 29, 51, 87, 80, 62},
		{18, 22, 37, 56, 68, 109, 103, 77},
		{24, 35, 55, 64, 81, 104, 113, 92},
		{49, 64, 78, 87, 103, 121, 120, 101},
		{72, 92, 95, 98, 112, 100, 103, 99}

		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1},
		// {1, 1, 1, 1, 1, 1, 1, 1}

		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200},
		// {200, 200, 200, 200, 200, 200, 200, 200}

		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300},
		// {300, 300, 300, 300, 300, 300, 300, 300}
	};

	// int** quantizationTable = new int*[N];
	// for (int i = 0; i < N; i++) {
	// 	quantizationTable[i] = new int[N];
	// }

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			quantizationTable[i][j] = tempquantizationTable[i][j];
		}
	}


	// double fitness = fitnessValueFromQuantizationTable(grayscaleArray, height, width, quantizationTable, cosine, coefficient);
	// cout << fitness << endl;

	int h;
	int w;

	int** pixels = new int*[N];
	for (int i = 0; i < N; i++) {
		pixels[i] = new int[N];
	}

	int previousDC;
	for (h = 0; h <= height - 8; h += 8) {
		for (w = 0; w <= width - 8; w += 8) {

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pixels[i][j] = ((double)grayscaleArray[h+i][w+j]);
				}
			}

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
						// cout << dct[dctY][dctX] << " ";
					}
					// cout << endl;
				}
				// cout << endl;
				for(int m = 0; m < encode.size(); m++) {
					// cout << (int)encode[m];
				}
				// cout << endl << endl;
			}
			huffmanEncode.insert(huffmanEncode.end(), encode.begin(), encode.end());

			// unquantizateDct(dct, quantizationTable);
			// double** pixels2 = generatePixels(dct, cosine, coefficient);
			

			// for (int i = 0; i < N; i++) {
			// 	for (int j = 0; j < N; j++) {
			// 		pixels2[i][j] = round(pixels2[i][j] + 128);
			// 		if (pixels2[i][j] > 255) {
			// 			pixels2[i][j] = 255;
			// 		}
			// 		if (pixels2[i][j] < 0) {
			// 			pixels2[i][j] = 0;
			// 		}
			// 		grayscaleArray[i+h][w+j] = (unsigned char)pixels2[i][j];
			// 		if(h == 24*8 && w == 19* 8)
			// 		{
			// 			//cout << pixels2[i][j] << "   ";
			// 		}
			// 	}
			// 	//if(h == 24*8 && w == 19* 8)
			// 		//cout << endl;
			// }

			for (int i = 0; i < N; i++) {
				delete alternativeDCT[i];
			}
			delete alternativeDCT;
		}
	}
	for (int i = 0; i < N; i++) {
		delete pixels[i];
	}
	delete pixels;
	
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
	myfile.close();
}
