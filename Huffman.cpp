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
	unsigned int runlength;
	unsigned int size;
	unsigned char hex;
	vector<bool> amp;
};

struct HuffmanMap {
	static map<unsigned char, string> CreateHuffmanMapAC() {
		map<unsigned char, string> huffmanMap;
		huffmanMap[0x01] = "00";
		huffmanMap[0x02] = "01";
		huffmanMap[0x03] = "100";
		huffmanMap[0x00] = "1010";
		huffmanMap[0x04] = "1011";
		huffmanMap[0x11] = "1100";
		huffmanMap[0x05] = "11010";
		huffmanMap[0x12] = "11011";
		huffmanMap[0x21] = "11100";
		huffmanMap[0x31] = "111010";
		huffmanMap[0x41] = "111011";
		huffmanMap[0x06] = "1111000";
		huffmanMap[0x13] = "1111001";
		huffmanMap[0x51] = "1111010";
		huffmanMap[0x61] = "1111011";
		huffmanMap[0x07] = "11111000";
		huffmanMap[0x22] = "11111001";
		huffmanMap[0x71] = "11111010";
		huffmanMap[0x14] = "111110110";
		huffmanMap[0x32] = "111110111";
		huffmanMap[0x81] = "111111000";
		huffmanMap[0x91] = "111111001";
		huffmanMap[0xA1] = "111111010";
		huffmanMap[0x08] = "1111110110";
		huffmanMap[0x23] = "1111110111";
		huffmanMap[0x42] = "1111111000";
		huffmanMap[0xB1] = "1111111001";
		huffmanMap[0xC1] = "1111111010";
		huffmanMap[0x15] = "11111110110";
		huffmanMap[0x52] = "11111110111";
		huffmanMap[0xD1] = "11111111000";
		huffmanMap[0xF0] = "11111111001";
		huffmanMap[0x24] = "111111110100";
		huffmanMap[0x33] = "111111110101";
		huffmanMap[0x62] = "111111110110";
		huffmanMap[0x72] = "111111110111";
		huffmanMap[0x82] = "111111111000000";
		huffmanMap[0x09] = "1111111110000010";
		huffmanMap[0x0A] = "1111111110000011";
		huffmanMap[0x16] = "1111111110000100";
		huffmanMap[0x17] = "1111111110000101";
		huffmanMap[0x18] = "1111111110000110";
		huffmanMap[0x19] = "1111111110000111";
		huffmanMap[0x1A] = "1111111110001000";
		huffmanMap[0x25] = "1111111110001001";
		huffmanMap[0x26] = "1111111110001010";
		huffmanMap[0x27] = "1111111110001011";
		huffmanMap[0x28] = "1111111110001100";
		huffmanMap[0x29] = "1111111110001101";
		huffmanMap[0x2A] = "1111111110001110";
		huffmanMap[0x34] = "1111111110001111";
		huffmanMap[0x35] = "1111111110010000";
		huffmanMap[0x36] = "1111111110010001";
		huffmanMap[0x37] = "1111111110010010";
		huffmanMap[0x38] = "1111111110010011";
		huffmanMap[0x39] = "1111111110010100";
		huffmanMap[0x3A] = "1111111110010101";
		huffmanMap[0x43] = "1111111110010110";
		huffmanMap[0x44] = "1111111110010111";
		huffmanMap[0x45] = "1111111110011000";
		huffmanMap[0x46] = "1111111110011001";
		huffmanMap[0x47] = "1111111110011010";
		huffmanMap[0x48] = "1111111110011011";
		huffmanMap[0x49] = "1111111110011100";
		huffmanMap[0x4A] = "1111111110011101";
		huffmanMap[0x53] = "1111111110011110";
		huffmanMap[0x54] = "1111111110011111";
		huffmanMap[0x55] = "1111111110100000";
		huffmanMap[0x56] = "1111111110100001";
		huffmanMap[0x57] = "1111111110100010";
		huffmanMap[0x58] = "1111111110100011";
		huffmanMap[0x59] = "1111111110100100";
		huffmanMap[0x5A] = "1111111110100101";
		huffmanMap[0x63] = "1111111110100110";
		huffmanMap[0x64] = "1111111110100111";
		huffmanMap[0x65] = "1111111110101000";
		huffmanMap[0x66] = "1111111110101001";
		huffmanMap[0x67] = "1111111110101010";
		huffmanMap[0x68] = "1111111110101011";
		huffmanMap[0x69] = "1111111110101100";
		huffmanMap[0x6A] = "1111111110101101";
		huffmanMap[0x73] = "1111111110101110";
		huffmanMap[0x74] = "1111111110101111";
		huffmanMap[0x75] = "1111111110110000";
		huffmanMap[0x76] = "1111111110110001";
		huffmanMap[0x77] = "1111111110110010";
		huffmanMap[0x78] = "1111111110110011";
		huffmanMap[0x79] = "1111111110110100";
		huffmanMap[0x7A] = "1111111110110101";
		huffmanMap[0x83] = "1111111110110110";
		huffmanMap[0x84] = "1111111110110111";
		huffmanMap[0x85] = "1111111110111000";
		huffmanMap[0x86] = "1111111110111001";
		huffmanMap[0x87] = "1111111110111010";
		huffmanMap[0x88] = "1111111110111011";
		huffmanMap[0x89] = "1111111110111100";
		huffmanMap[0x8A] = "1111111110111101";
		huffmanMap[0x92] = "1111111110111110";
		huffmanMap[0x93] = "1111111110111111";
		huffmanMap[0x94] = "1111111111000000";
		huffmanMap[0x95] = "1111111111000001";
		huffmanMap[0x96] = "1111111111000010";
		huffmanMap[0x97] = "1111111111000011";
		huffmanMap[0x98] = "1111111111000100";
		huffmanMap[0x99] = "1111111111000101";
		huffmanMap[0x9A] = "1111111111000110";
		huffmanMap[0xA2] = "1111111111000111";
		huffmanMap[0xA3] = "1111111111001000";
		huffmanMap[0xA4] = "1111111111001001";
		huffmanMap[0xA5] = "1111111111001010";
		huffmanMap[0xA6] = "1111111111001011";
		huffmanMap[0xA7] = "1111111111001100";
		huffmanMap[0xA8] = "1111111111001101";
		huffmanMap[0xA9] = "1111111111001110";
		huffmanMap[0xAA] = "1111111111001111";
		huffmanMap[0xB2] = "1111111111010000";
		huffmanMap[0xB3] = "1111111111010001";
		huffmanMap[0xB4] = "1111111111010010";
		huffmanMap[0xB5] = "1111111111010011";
		huffmanMap[0xB6] = "1111111111010100";
		huffmanMap[0xB7] = "1111111111010101";
		huffmanMap[0xB8] = "1111111111010110";
		huffmanMap[0xB9] = "1111111111010111";
		huffmanMap[0xBA] = "1111111111011000";
		huffmanMap[0xC2] = "1111111111011001";
		huffmanMap[0xC3] = "1111111111011010";
		huffmanMap[0xC4] = "1111111111011011";
		huffmanMap[0xC5] = "1111111111011100";
		huffmanMap[0xC6] = "1111111111011101";
		huffmanMap[0xC7] = "1111111111011110";
		huffmanMap[0xC8] = "1111111111011111";
		huffmanMap[0xC9] = "1111111111100000";
		huffmanMap[0xCA] = "1111111111100001";
		huffmanMap[0xD2] = "1111111111100010";
		huffmanMap[0xD3] = "1111111111100011";
		huffmanMap[0xD4] = "1111111111100100";
		huffmanMap[0xD5] = "1111111111100101";
		huffmanMap[0xD6] = "1111111111100110";
		huffmanMap[0xD7] = "1111111111100111";
		huffmanMap[0xD8] = "1111111111101000";
		huffmanMap[0xD9] = "1111111111101001";
		huffmanMap[0xDA] = "1111111111101010";
		huffmanMap[0xE1] = "1111111111101011";
		huffmanMap[0xE2] = "1111111111101100";
		huffmanMap[0xE3] = "1111111111101101";
		huffmanMap[0xE4] = "1111111111101110";
		huffmanMap[0xE5] = "1111111111101111";
		huffmanMap[0xE6] = "1111111111110000";
		huffmanMap[0xE7] = "1111111111110001";
		huffmanMap[0xE8] = "1111111111110010";
		huffmanMap[0xE9] = "1111111111110011";
		huffmanMap[0xEA] = "1111111111110100";
		huffmanMap[0xF1] = "1111111111110101";
		huffmanMap[0xF2] = "1111111111110110";
		huffmanMap[0xF3] = "1111111111110111";
		huffmanMap[0xF4] = "1111111111111000";
		huffmanMap[0xF5] = "1111111111111001";
		huffmanMap[0xF6] = "1111111111111010";
		huffmanMap[0xF7] = "1111111111111011";
		huffmanMap[0xF8] = "1111111111111100";
		huffmanMap[0xF9] = "1111111111111101";
		huffmanMap[0xFA] = "1111111111111110";
		return huffmanMap;
	}
	static map<unsigned char, string> CreateHuffmanMapDC() {
		map<unsigned char, string> huffmanMap;
		huffmanMap[0x00] = "00";
		huffmanMap[0x01] = "010";
		huffmanMap[0x02] = "011";
		huffmanMap[0x03] = "100";
		huffmanMap[0x04] = "101";
		huffmanMap[0x05] = "110";
		huffmanMap[0x06] = "1110";
		huffmanMap[0x07] = "11110";
		huffmanMap[0x08] = "111110";
		huffmanMap[0x09] = "1111110";
		huffmanMap[0x0A] = "11111110";
		huffmanMap[0x0B] = "111111110";
		return huffmanMap;
	}
	static const map<unsigned char, string> hmapAC;
	static const map<unsigned char, string> hmapDC;
};
const map<unsigned char, string> HuffmanMap::hmapAC = HuffmanMap::CreateHuffmanMapAC();
const map<unsigned char, string> HuffmanMap::hmapDC = HuffmanMap::CreateHuffmanMapDC();


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

vector<unsigned char> ConvertQuantizationHeader(int** quant)
{
	vector<unsigned char> header;
	int** q = new int*[N];
	header.push_back(0xFF);
header.push_back(0xDB);
//Bytes After
header.push_back(0x00);
header.push_back(0x43);
//ID
header.push_back(0x00);
	for (int i = 0; i < N; i++) {
		q[i] = new int[N];
		for(int j = 0; j < N; j++) {
			q[i][j] = quant[i][j];
		}
	}
	int* zig = ZigZagMatrix(q);
	for(int i = 0; i < N*N; i++)
	{
		header.push_back((unsigned char) zig[i]);
	}
	delete [] zig;
	for(int i = 0; i < N; i++)
	{
		delete[] q[i];
	}
	delete [] q;
	return header;
}

unsigned int GetSize(int num) {
	if(num < 0) {
		num *= -1;
	}
	unsigned int size = 0;
	while(num >= (1 << size)) {
		size++;
	}
	return size;
}
vector<bool> GetAmp(int num, int size) {
	vector<bool> amp;
	bool neg = false;
	if(num < 0) {
		neg = true;
		num *= -1;
	}
	for(int i = size - 1; i >= 0; i--)
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
	unsigned int zeroes = 0;
	int encodingCount = 0;
	for(int i = 0; i < N * N; i++) {
		if(d[i] != 0 || i == 0) {
			while(zeroes >= 16) {
				encoding.push_back(RLE());
				encoding[encodingCount].runlength = 15;
				encoding[encodingCount].size = 0;
				encoding[encodingCount].hex = 
					encoding[encodingCount].runlength << 4 ^ encoding[encodingCount].size;
				zeroes -=16;
				encodingCount++;
			}
			if(i == 0)
			{
				//d[i] -= 150;
			}
			encoding.push_back(RLE());
			encoding[encodingCount].runlength = zeroes;
			encoding[encodingCount].size = GetSize(d[i]);
			encoding[encodingCount].amp = GetAmp(d[i], encoding[encodingCount].size);
			encoding[encodingCount].hex = 
				encoding[encodingCount].runlength << 4 ^ encoding[encodingCount].size;
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
		//hex is 00
	}
	return encoding;
}

void printRLE(vector<RLE> encoding) {
	for(int i = 0; i < encoding.size(); i++)
	{
		cout << "( " << encoding[i].runlength << " ";
		cout << ", " <<  encoding[i].size << ") ";
		if(i == 0)
			cout << HuffmanMap::hmapDC.at(encoding[i].hex) << " ";
		else
			cout << HuffmanMap::hmapAC.at(encoding[i].hex) << " ";
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

vector<bool> RLEToBits(vector<RLE> encoding) {
	vector<bool> bits;
	for(int i = 0; i < encoding.size(); i++)
	{
		string huffmanString;
		if(i == 0) {
			//cout << "DC " << hex << (int)encoding[i].hex << endl;
			huffmanString = HuffmanMap::hmapDC.at(encoding[i].hex);

		}
		else {
			//cout << "AC " << hex << (int)encoding[i].hex << endl;
			huffmanString = HuffmanMap::hmapAC.at(encoding[i].hex);

		}
		for(int j = 0; j < huffmanString.size(); j++) {
			if(huffmanString[j] == '1') {
				bits.push_back(true);			
			}
			else {
				bits.push_back(false);
			}
		}
		bits.insert(bits.end(), encoding[i].amp.begin(), encoding[i].amp.end()); 
	}
	return bits;
}

vector<bool> HuffmanEncode(int** pixels) {
	int* zigzag = ZigZagMatrix(pixels);
	
	vector<RLE> encoding = EncodeRLE(zigzag);
	//printRLE(encoding);
	vector<bool> encode = RLEToBits(encoding);
	delete [] zigzag;
	return encode;
}

vector<unsigned char> GetHuffmanDC() {
	vector<unsigned char> huffmanDC;
	huffmanDC.push_back(0xff);
	huffmanDC.push_back(0xc4);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x1f);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x05);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x00);
	huffmanDC.push_back(0x01);
	huffmanDC.push_back(0x02);
	huffmanDC.push_back(0x03);
	huffmanDC.push_back(0x04);
	huffmanDC.push_back(0x05);
	huffmanDC.push_back(0x06);
	huffmanDC.push_back(0x07);
	huffmanDC.push_back(0x08);
	huffmanDC.push_back(0x09);
	huffmanDC.push_back(0x0a);
	huffmanDC.push_back(0x0b);
	return huffmanDC;
}

vector<unsigned char> GetHuffmanAC() {
	vector<unsigned char> huffmanAC;
	huffmanAC.push_back(0xff);
huffmanAC.push_back(0xc4);
huffmanAC.push_back(0x00);
huffmanAC.push_back(0xb5);
huffmanAC.push_back(0x10);
huffmanAC.push_back(0x00);
huffmanAC.push_back(0x02);
huffmanAC.push_back(0x01);
huffmanAC.push_back(0x03);
huffmanAC.push_back(0x03);
huffmanAC.push_back(0x02);
huffmanAC.push_back(0x04);
huffmanAC.push_back(0x03);
huffmanAC.push_back(0x05);
huffmanAC.push_back(0x05);
huffmanAC.push_back(0x04);
huffmanAC.push_back(0x04);
huffmanAC.push_back(0x00);
huffmanAC.push_back(0x00);
huffmanAC.push_back(0x01);
huffmanAC.push_back(0x7d);
huffmanAC.push_back(0x01);
huffmanAC.push_back(0x02);
huffmanAC.push_back(0x03);
huffmanAC.push_back(0x00);
huffmanAC.push_back(0x04);
huffmanAC.push_back(0x11);
huffmanAC.push_back(0x05);
huffmanAC.push_back(0x12);
huffmanAC.push_back(0x21);
huffmanAC.push_back(0x31);
huffmanAC.push_back(0x41);
huffmanAC.push_back(0x06);
huffmanAC.push_back(0x13);
huffmanAC.push_back(0x51);
huffmanAC.push_back(0x61);
huffmanAC.push_back(0x07);
huffmanAC.push_back(0x22);
huffmanAC.push_back(0x71);
huffmanAC.push_back(0x14);
huffmanAC.push_back(0x32);
huffmanAC.push_back(0x81);
huffmanAC.push_back(0x91);
huffmanAC.push_back(0xa1);
huffmanAC.push_back(0x08);
huffmanAC.push_back(0x23);
huffmanAC.push_back(0x42);
huffmanAC.push_back(0xb1);
huffmanAC.push_back(0xc1);
huffmanAC.push_back(0x15);
huffmanAC.push_back(0x52);
huffmanAC.push_back(0xd1);
huffmanAC.push_back(0xf0);
huffmanAC.push_back(0x24);
huffmanAC.push_back(0x33);
huffmanAC.push_back(0x62);
huffmanAC.push_back(0x72);
huffmanAC.push_back(0x82);
huffmanAC.push_back(0x09);
huffmanAC.push_back(0x0a);
huffmanAC.push_back(0x16);
huffmanAC.push_back(0x17);
huffmanAC.push_back(0x18);
huffmanAC.push_back(0x19);
huffmanAC.push_back(0x1a);
huffmanAC.push_back(0x25);
huffmanAC.push_back(0x26);
huffmanAC.push_back(0x27);
huffmanAC.push_back(0x28);
huffmanAC.push_back(0x29);
huffmanAC.push_back(0x2a);
huffmanAC.push_back(0x34);
huffmanAC.push_back(0x35);
huffmanAC.push_back(0x36);
huffmanAC.push_back(0x37);
huffmanAC.push_back(0x38);
huffmanAC.push_back(0x39);
huffmanAC.push_back(0x3a);
huffmanAC.push_back(0x43);
huffmanAC.push_back(0x44);
huffmanAC.push_back(0x45);
huffmanAC.push_back(0x46);
huffmanAC.push_back(0x47);
huffmanAC.push_back(0x48);
huffmanAC.push_back(0x49);
huffmanAC.push_back(0x4a);
huffmanAC.push_back(0x53);
huffmanAC.push_back(0x54);
huffmanAC.push_back(0x55);
huffmanAC.push_back(0x56);
huffmanAC.push_back(0x57);
huffmanAC.push_back(0x58);
huffmanAC.push_back(0x59);
huffmanAC.push_back(0x5a);
huffmanAC.push_back(0x63);
huffmanAC.push_back(0x64);
huffmanAC.push_back(0x65);
huffmanAC.push_back(0x66);
huffmanAC.push_back(0x67);
huffmanAC.push_back(0x68);
huffmanAC.push_back(0x69);
huffmanAC.push_back(0x6a);
huffmanAC.push_back(0x73);
huffmanAC.push_back(0x74);
huffmanAC.push_back(0x75);
huffmanAC.push_back(0x76);
huffmanAC.push_back(0x77);
huffmanAC.push_back(0x78);
huffmanAC.push_back(0x79);
huffmanAC.push_back(0x7a);
huffmanAC.push_back(0x83);
huffmanAC.push_back(0x84);
huffmanAC.push_back(0x85);
huffmanAC.push_back(0x86);
huffmanAC.push_back(0x87);
huffmanAC.push_back(0x88);
huffmanAC.push_back(0x89);
huffmanAC.push_back(0x8a);
huffmanAC.push_back(0x92);
huffmanAC.push_back(0x93);
huffmanAC.push_back(0x94);
huffmanAC.push_back(0x95);
huffmanAC.push_back(0x96);
huffmanAC.push_back(0x97);
huffmanAC.push_back(0x98);
huffmanAC.push_back(0x99);
huffmanAC.push_back(0x9a);
huffmanAC.push_back(0xa2);
huffmanAC.push_back(0xa3);
huffmanAC.push_back(0xa4);
huffmanAC.push_back(0xa5);
huffmanAC.push_back(0xa6);
huffmanAC.push_back(0xa7);
huffmanAC.push_back(0xa8);
huffmanAC.push_back(0xa9);
huffmanAC.push_back(0xaa);
huffmanAC.push_back(0xb2);
huffmanAC.push_back(0xb3);
huffmanAC.push_back(0xb4);
huffmanAC.push_back(0xb5);
huffmanAC.push_back(0xb6);
huffmanAC.push_back(0xb7);
huffmanAC.push_back(0xb8);
huffmanAC.push_back(0xb9);
huffmanAC.push_back(0xba);
huffmanAC.push_back(0xc2);
huffmanAC.push_back(0xc3);
huffmanAC.push_back(0xc4);
huffmanAC.push_back(0xc5);
huffmanAC.push_back(0xc6);
huffmanAC.push_back(0xc7);
huffmanAC.push_back(0xc8);
huffmanAC.push_back(0xc9);
huffmanAC.push_back(0xca);
huffmanAC.push_back(0xd2);
huffmanAC.push_back(0xd3);
huffmanAC.push_back(0xd4);
huffmanAC.push_back(0xd5);
huffmanAC.push_back(0xd6);
huffmanAC.push_back(0xd7);
huffmanAC.push_back(0xd8);
huffmanAC.push_back(0xd9);
huffmanAC.push_back(0xda);
huffmanAC.push_back(0xe1);
huffmanAC.push_back(0xe2);
huffmanAC.push_back(0xe3);
huffmanAC.push_back(0xe4);
huffmanAC.push_back(0xe5);
huffmanAC.push_back(0xe6);
huffmanAC.push_back(0xe7);
huffmanAC.push_back(0xe8);
huffmanAC.push_back(0xe9);
huffmanAC.push_back(0xea);
huffmanAC.push_back(0xf1);
huffmanAC.push_back(0xf2);
huffmanAC.push_back(0xf3);
huffmanAC.push_back(0xf4);
huffmanAC.push_back(0xf5);
huffmanAC.push_back(0xf6);
huffmanAC.push_back(0xf7);
huffmanAC.push_back(0xf8);
huffmanAC.push_back(0xf9);
huffmanAC.push_back(0xfa);
	return huffmanAC;
}
/**
int main(int argc, char** argv) {
	int x[8][8] = {
		{  -78,  104,    6,   -1,    0,    0,    0,    0},
		{   74,  -17,   -9,    0,   -3,    0,    0,    0},
		{   -4,  -10,   10,   -4,    1,    0,    0,    0},
		{   -1,    5,   -3,    0,    1,    0,    0,    0},
		{   -1,   -1,    0,    0,    0,    0,    0,    0},
		{    1,    1,    0,    0,    0,    0,    0,    0},
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

	vector<bool> full = HuffmanEncode(pixels);
	
	for(int i = 0; i < full.size(); i++) {
		if(full[i])
			cout << "1";
		else
			cout << "0";
	}
	cout << endl;
}**/
