#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

struct Scanner
{
	unsigned int depth = 0;
	unsigned int pos = 0;
	unsigned int range = 0;
	unsigned int states = 0;
};

void parseInput(std::vector<Scanner> &scanners)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			Scanner scanner;
			size_t pos = 0;
			size_t endpos = line.find_first_of(":");
			scanner.depth = std::stoi(line.substr(0, endpos));
			
			pos = line.find_first_of("1234567890", endpos);
			scanner.range = std::stoi(line.substr(pos));
			scanner.states = scanner.range*2 - 2;
			scanner.pos = scanner.depth%scanner.states;
			
			scanners.push_back(scanner);
		}
	}
	input.close();
}

uint64_t calculateSeverity(std::vector<Scanner> &scanners)
{
	uint64_t result = 0;

	for(unsigned int i=0; i<scanners.size(); i++)
	{
		if(scanners[i].pos == 0)
		{
			result += scanners[i].depth*scanners[i].range;
		}
	}
	
	return result;
}

uint64_t calculateDelay(std::vector<Scanner> &scanners)
{
	uint64_t result = 0;
	bool found = false;
	
	while(!found)
	{
		found = true;
		for(unsigned int i=0; i<scanners.size(); i++)
		{
			if(scanners[i].pos == 0)
			{
				found = false;
			}
			scanners[i].pos += 2;
			scanners[i].pos %= scanners[i].states;
		}
		if(!found)
		{
			result += 2;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<Scanner> scanners;
	
	parseInput(scanners);
	
	resultA = calculateSeverity(scanners);
	resultB = calculateDelay(scanners);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
