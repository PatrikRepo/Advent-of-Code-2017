#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<int> &jumps)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			int jump = std::stoi(line);
			jumps.push_back(jump);
		}
	}
	input.close();
}

uint64_t calculateJumps(std::vector<int> jumps, bool withDecrease)
{
	uint64_t result = 0;
	unsigned int i=0;
	while(i<jumps.size())
	{
		result++;
		int offset = jumps[i];
		if(withDecrease && offset >= 3)
		{
			jumps[i] -= 1;
		}
		else
		{
			jumps[i] += 1;
		}
		i += offset;
	}

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<int> jumps;
	
	parseInput(jumps);
	
	resultA = calculateJumps(jumps, false);
	resultB = calculateJumps(jumps, true);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
