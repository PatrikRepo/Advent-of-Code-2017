#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

void parseInput(std::vector<unsigned int> &memory)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		size_t pos = line.find_first_of("1234567890");
		size_t endpos = 0;
		
		while(pos != std::string::npos)
		{
			endpos = line.find_first_not_of("1234567890", pos);
			int number = std::stoi(line.substr(pos, endpos-pos));
			memory.push_back(number);
			pos = line.find_first_of("1234567890", endpos);
		}
	}
	input.close();
}

std::string makeString(const std::vector<unsigned int> &memory)
{
	std::string result;
	
	for(unsigned int i=0; i<memory.size(); i++)
	{
		result += std::to_string(memory[i]) + " ";
	}
	
	return result;
}

std::pair<uint64_t,uint64_t> distributeMemory(std::vector<unsigned int> &memory)
{
	std::pair<uint64_t,uint64_t> result;
	unsigned int memSize = memory.size();
	std::unordered_map<std::string, unsigned int> cache;
	bool foundLoop = false;
	std::string loopStart;
	
	while(!foundLoop)
	{
		result.first++;
		unsigned int max = 0;
		unsigned int index = 0;

		for(unsigned int i=0; i<memSize; i++)
		{
			if(max < memory[i])
			{
				max = memory[i];
				index = i;
			}
		}
		memory[index] = 0;
		while(max > 0)
		{
			index = (index+1)%memSize;
			max--;
			memory[index]++;
		}
		std::string stringRep = makeString(memory);
		if(cache.count(stringRep) == 1)
		{
			foundLoop = true;
			loopStart = stringRep;
			break;
		}
		cache[stringRep] += 1;
	}
	
	bool loopTraversed = false;
	while(!loopTraversed)
	{
		result.second++;
		unsigned int max = 0;
		unsigned int index = 0;
		for(unsigned int i=0; i<memSize; i++)
		{
			if(max < memory[i])
			{
				max = memory[i];
				index = i;
			}
		}
		memory[index] = 0;
		while(max > 0)
		{
			index = (index+1)%memSize;
			max--;
			memory[index]++;
		}
		std::string stringRep = makeString(memory);
		if(stringRep == loopStart)
		{
			loopTraversed = true;
			break;
		}
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::vector<unsigned int> memory;
	
	parseInput(memory);
	
	result = distributeMemory(memory);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
