#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <bitset>

void parseInput(std::vector<std::vector<unsigned int>> &rows)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		for(int i=0; i<128; i++)
		{
			std::string rowString = line + '-' + std::to_string(i);
			std::vector<unsigned int> row;
			for(unsigned int i=0; i<rowString.length(); i++)
			{
				row.push_back((unsigned int)rowString[i]);
			}
			row.push_back(17);
			row.push_back(31);
			row.push_back(73);
			row.push_back(47);
			row.push_back(23);
			
			rows.push_back(row);
		}		
	}
	input.close();
}

uint64_t calculateKnotHash(std::vector<unsigned int> &row, std::vector<std::string> &map)
{
	uint64_t result = 0;
	unsigned int arr[256];
	for(int i=0; i<256; i++)
	{
		arr[i] = i;
	}
	unsigned int pos = 0;
	unsigned skip = 0;
	
	for(unsigned int k=0; k<64; k++)
	{
		for(unsigned int i=0; i<row.size(); i++)
		{
			unsigned int newArr[row[i]];
			for(unsigned int j=0; j<row[i]; j++)
			{
				newArr[row[i]-1-j] = arr[(pos+j)%256];
			}
			for(unsigned int j=0; j<row[i]; j++)
			{
				arr[(pos+j)%256] = newArr[j];
			}
			pos += row[i] + skip;
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
	std::string knotHash = hexer.str();
	std::string memoryString;
	for(unsigned int i=0; i<knotHash.length(); i++)
	{
		unsigned int num = 0;
		if(knotHash[i] >= '0' && knotHash[i] <= '9')
		{
			num = knotHash[i] - '0';
		}
		else
		{
			num = knotHash[i] - 'a' + 10;
		}
		std::bitset<4> bits(num);
		memoryString += bits.to_string();
		result += bits.count();
	}
	
	map.push_back(memoryString);

	return result;
}

void clearGroup(std::vector<std::string> &map, const unsigned int x, const unsigned int y)
{
	if(map[y][x] == '1')
	{
		map[y][x] = '0';
		if(x > 0)
		{
			clearGroup(map, x-1, y);
		}
		if(x+1 < map[0].length())
		{
			clearGroup(map, x+1, y);
		}
		if(y > 0)
		{
			clearGroup(map, x, y-1);
		}
		if(y+1 < map.size())
		{
			clearGroup(map, x, y+1);
		}
	}	
}

std::pair<uint64_t,uint64_t> calculateMemoryUsed(std::vector<std::vector<unsigned int>> &rows)
{
	std::pair<uint64_t,uint64_t> result = {0,0};
	std::vector<std::string> map;
	
	for(unsigned int i=0; i<rows.size(); i++)
	{	
		result.first += calculateKnotHash(rows[i], map);
	}
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] == '1')
			{
				result.second += 1;
				clearGroup(map, j, i);
			}
		}
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::vector<std::vector<unsigned int>> rows;
	
	parseInput(rows);
	
	result = calculateMemoryUsed(rows);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
