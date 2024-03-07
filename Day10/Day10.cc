#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

void parseInput(std::vector<unsigned int> &lengths, std::vector<unsigned int> &bigLengths)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		if(getline(input, line))
		{
			size_t pos = 0;
			size_t endpos = line.find_first_of(",",pos);
			unsigned int length;
			while(endpos != std::string::npos)
			{
				length = std::stoi(line.substr(pos, endpos-pos));
				lengths.push_back(length);
				pos = endpos +1;
				endpos = line.find_first_of(",",pos);
			}
			length = std::stoi(line.substr(pos));
			lengths.push_back(length);
			for(unsigned int i=0; i<line.length(); i++)
			{
				bigLengths.push_back((unsigned int)line[i]);
			}
		}
		bigLengths.push_back(17);
		bigLengths.push_back(31);
		bigLengths.push_back(73);
		bigLengths.push_back(47);
		bigLengths.push_back(23);
	}
	input.close();
}

uint64_t calculateKnotHash(const std::vector<unsigned int> &lengths)
{
	uint64_t result = 0;
	unsigned int arr[256];
	for(int i=0; i<256; i++)
	{
		arr[i] = i;
	}
	unsigned int pos = 0;
	unsigned skip = 0;
	
	for(unsigned int i=0; i<lengths.size(); i++)
	{
		unsigned int newArr[lengths[i]];
		for(unsigned int j=0; j<lengths[i]; j++)
		{
			newArr[lengths[i]-1-j] = arr[(pos+j)%256];
		}
		for(unsigned int j=0; j<lengths[i]; j++)
		{
			arr[(pos+j)%256] = newArr[j];
		}
		pos += (lengths[i] + skip)%256;
		skip++;
	}
	result = arr[0]*arr[1];
	
	return result;
}

std::string calculateBigKnotHash(const std::vector<unsigned int> &lengths)
{
	std::string result;
	unsigned int arr[256];
	for(int i=0; i<256; i++)
	{
		arr[i] = i;
	}
	unsigned int pos = 0;
	unsigned skip = 0;
	
	for(unsigned int k=0; k<64; k++)
	{
		for(unsigned int i=0; i<lengths.size(); i++)
		{
			unsigned int newArr[lengths[i]];
			for(unsigned int j=0; j<lengths[i]; j++)
			{
				newArr[lengths[i]-1-j] = arr[(pos+j)%256];
			}
			for(unsigned int j=0; j<lengths[i]; j++)
			{
				arr[(pos+j)%256] = newArr[j];
			}
			pos += lengths[i] + skip;
			pos %= 256;
			skip = (skip+1)%256;
		}
	}

	std::vector<unsigned int> denseHash;
	
	for(int i=0; i<16; i++)
	{
		unsigned int hashNum = arr[16*i];
		for(int j=16*i+1; j<16*(i+1); j++)
		{
			hashNum ^= arr[j];
		}
		denseHash.push_back(hashNum);
	}

	std::stringstream hexer;
	for(unsigned int i=0; i<denseHash.size(); i++)
	{
		hexer << std::hex << std::setw(2) << std::setfill('0') << denseHash[i];
	}
	
	result = hexer.str();
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	std::string resultB;
	std::vector<unsigned int> lengths;
	std::vector<unsigned int> bigLengths;
	
	parseInput(lengths, bigLengths);
	
	resultA = calculateKnotHash(lengths);
	resultB = calculateBigKnotHash(bigLengths);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
