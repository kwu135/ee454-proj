#include "Huffman.h"
using namespace std;

struct zigzag {
int row;
int col;
} ZigZag[ N * N ] =
{
{0, 0},
{0, 1}, {1, 0},
{2, 0}, {1, 1}, {0, 2},
{0, 3}, {1, 2}, {2, 1}, {3, 0},
{4, 0}, {3, 1}, {2, 2}, {1, 3}, {0, 4},
{0, 5}, {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0},
{6, 0}, {5, 1}, {4, 2}, {3, 3}, {2, 4}, {1, 5}, {0, 6},
{0, 7}, {1, 6}, {2, 5}, {3, 4}, {4, 3}, {5, 2}, {6, 1}, {7, 0},
{7, 1}, {6, 2}, {5, 3}, {4, 4}, {3, 5}, {2, 6}, {1, 7},
{2, 7}, {3, 6}, {4, 5}, {5, 4}, {6, 3}, {7, 2},
{7, 3}, {6, 4}, {5, 5}, {4, 6}, {3, 7},
{4, 7}, {5, 6}, {6, 5}, {7, 4},
{7, 5}, {6, 6}, {5, 7},
{6, 7}, {7, 6},
{7, 7}
};

struct RLE {
	int runlength;
	int size;
	bitset<8> bits;
	vector<bool> amp;
};

int* ZigZagMatrix(int** m) {
	int* zigzag = new int[N*N];
	
	int row;
	int col;
	
	for(int i = 0; i < N * N; i++)
	{
		row = ZigZag[i].row;
		col = ZigZag[i].col;
		zigzag[i] = m[row][col];
	}

	return zigzag;
}

int** UnZigZagMatrix(int* m) {
	int** unzigzag = new int*[N];
	for (int i = 0; i < N; i++) {
		unzigzag[i] = new int[N];
	}
	
	int row;
	int col;	
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			row = ZigZag[i*8 + j].row;
			col = ZigZag[i*8 + j].col;
			unzigzag[row][col] = m[i*8+j];
		}
	}

	return unzigzag;
}

int GetSize(int num) {
	if(num < 0) {
		num *= -1;
	}
	unsigned int size = 0;
	while(num > (1 << size)) {
		size++;
	}
	return size + 1;
}
vector<bool> GetAmp(int num, int size) {
	vector<bool> amp;
	bool neg = false;
	if(num < 0) {
		neg = true;
		num *= -1;
		amp.push_back(false);	
	}
	else{
		amp.push_back(true);	
	}
	for(int i = size - 2; i >= 0; i--)
	{
		if((1 << i) <= num)
		{
			num -= (1 << i);
			if(neg) {
				amp.push_back(false);			
			}
			else {
				amp.push_back(true);
			}
		}
		else {
			if(neg) {
				amp.push_back(true);			
			}
			else {
				amp.push_back(false);
			}
		}
	}
	return amp;
}

vector<RLE> EncodeRLE(int* d) {
	vector<RLE> encoding;
	int zeroes = 0;
	int encodingCount = 0;
	for(int i = 0; i < N * N; i++) {
		if(d[i] != 0) {
			encoding.push_back(RLE());
			encoding[encodingCount].runlength = zeroes;
			encoding[encodingCount].size = GetSize(d[i]);
			encoding[encodingCount].amp = GetAmp(d[i], encoding[encodingCount].size);
			encodingCount++;
			zeroes = 0;
		}
		else{
			zeroes++;		
		}
	}
	if(zeroes > 0) {
		encoding.push_back(RLE());
		encoding[encodingCount].runlength = zeroes;
	}
	return encoding;
}

int main(int argc, char** argv) {
	int x[8][8] = {
		{  -43, -109,    8,   -6,    2,   -1,    0,    0},
		{  153,  -70,  -11,    2,   -1,    0,    0,    0},
		{   22,   16,  -14,    0,   -1,    0,    0,    0},
		{    2,   14,    1,  -2,    0,    0,    0,    0},
		{    3,    2,    0,    0,    0,    0,    0,    0},
		{    2,    0,    0,    0,    0,    0,    0,    0},
		{    0,    0,    0,    0,    0,    0,    0,    0},
		{    0,    0,    0,    0,    0,    0,    0,    0}
	};
	int** pixels = new int*[N];
	for (int i = 0; i < N; i++) {
		pixels[i] = new int[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			pixels[i][j] = x[i][j];
		}
	}


	int* zigzag = ZigZagMatrix(pixels);
	
	vector<RLE> encoding = EncodeRLE(zigzag);	

	for(int i = 0; i < encoding.size(); i++)
	{
		cout << "( " << encoding[i].runlength << ", " <<  encoding[i].size 
		<< ") ";
		for(int j = 0; j < encoding[i].amp.size(); j++) {
			if(encoding[i].amp[j]) {
				cout << "1";			
			}
			else {
				cout << "0";
			}
		}
		cout << ", ";
	}
	cout<<endl;
}
