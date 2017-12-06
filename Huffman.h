#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <string>
#define N 8

using namespace std;

vector<bool> HuffmanEncode(int** pixels);
vector<unsigned char> ConvertQuantizationHeader(int** quant);
vector<unsigned char> GetHuffmanAC();
vector<unsigned char> GetHuffmanDC();
