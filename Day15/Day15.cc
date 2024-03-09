#include <iostream>
#include <fstream>
#include <utility>
#include <bitset>

void parseInput(std::pair<uint64_t, uint64_t> &startingNumbers)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		size_t pos = line.find_first_of("1234567890");
		startingNumbers.first = std::stoi(line.substr(pos));
		
		getline(input, line);
		pos = line.find_first_of("1234567890");
		startingNumbers.second = std::stoi(line.substr(pos));		
	}
	input.close();
}

std::pair<uint64_t,uint64_t> calculateGeneratorMatches(const std::pair<uint64_t,uint64_t> &startingNumbers)
{
	std::pair<uint64_t,uint64_t> result;
	uint64_t genAPrevious = startingNumbers.first;
	uint64_t genBPrevious = startingNumbers.second;
	const unsigned int genAFactor = 16807;
	const unsigned int genBFactor = 48271;
	const unsigned int divisor = 2147483647;
	std::bitset<16> genABits;
	std::bitset<16> genBBits;
	
	for(unsigned int i=0; i<40000000; i++)
	{
		genAPrevious = (genAPrevious*genAFactor)%divisor;
		genBPrevious = (genBPrevious*genBFactor)%divisor;
		genABits = genAPrevious;
		genBBits = genBPrevious;
		if(genABits == genBBits)
		{
			result.first += 1;
		}
	}
	
	genAPrevious = startingNumbers.first;
	genBPrevious = startingNumbers.second;
	
	for(unsigned int i=0; i<5000000; i++)
	{
		genAPrevious = (genAPrevious*genAFactor)%divisor;
		while(genAPrevious % 4 != 0)
		{
			genAPrevious = (genAPrevious*genAFactor)%divisor;
		}

		genBPrevious = (genBPrevious*genBFactor)%divisor;
		while(genBPrevious % 8 != 0)
		{
			genBPrevious = (genBPrevious*genBFactor)%divisor;
		}
		
		genABits = genAPrevious;
		genBBits = genBPrevious;
		if(genABits == genBBits)
		{
			result.second += 1;
		}
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::pair<uint64_t,uint64_t> startingNumbers;
	
	parseInput(startingNumbers);
	
	result = calculateGeneratorMatches(startingNumbers);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
