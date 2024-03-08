#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<std::pair<unsigned int, std::vector<unsigned int>>> &scanners)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = 0;
			size_t endpos = line.find_first_of(":");
			unsigned int depth = std::stoi(line.substr(0, endpos));
			
			pos = line.find_first_of("1234567890", endpos);
			unsigned int range = std::stoi(line.substr(pos));
			
			std::vector<unsigned int> layer;
			for(unsigned int i=0; i<range; i++)
			{
				layer.push_back(0);
			}	
			
			bool down = true;
			if((depth/(range-1))%2 == 1)
			{
				down = false;
			}
			if(down)
			{
				layer[depth%(range-1)] = 1;
			}
			else
			{
				layer[range-1 - (depth%(range-1))] = 1;
			}
			
			scanners.push_back(std::make_pair(depth, layer));
		}
	}
	input.close();
}

uint64_t calculateSeverity(std::vector<std::pair<unsigned int, std::vector<unsigned int>>> &scanners)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<scanners.size(); i++)
	{
		if(scanners[i].second[0] == 1)
		{
			result += scanners[i].first*scanners[i].second.size();
		}
	}
	
	return result;
}

void moveStep(std::pair<unsigned int, std::vector<unsigned int>> &scanner, uint64_t step)
{
	bool down = true;
	unsigned int depth = scanner.first;
	unsigned int range = scanner.second.size();
	
	if(((step + depth)/(range-1))%2 == 1)
	{
		down = false;
	}
	if(down)
	{
		scanner.second[(step + depth)%(range-1)] = 0;
	}
	else
	{
		scanner.second[range-1 - ((step + depth)%(range-1))] = 0;
	}
	down = true;
	if(((step + 1 + depth)/(range-1))%2 == 1)
	{
		down = false;
	}
	if(down)
	{
		scanner.second[(step + 1 + depth)%(range-1)] = 1;
	}
	else
	{
		scanner.second[range-1 - ((step + 1 + depth)%(range-1))] = 1;
	}
}

uint64_t calculateDelay(std::vector<std::pair<unsigned int, std::vector<unsigned int>>> &scanners)
{
	uint64_t result = 0;
	bool found = false;
	
	while(!found)
	{
		found = true;
		for(unsigned int i=0; i<scanners.size(); i++)
		{
			if(scanners[i].second[0] == 1)
			{
				found = false;
			}
			moveStep(scanners[i], result);
		}
		if(!found)
		{
			result++;
		}
	}

	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::pair<unsigned int, std::vector<unsigned int>>> scanners;
	
	parseInput(scanners);
	
	resultA = calculateSeverity(scanners);
	resultB = calculateDelay(scanners);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
