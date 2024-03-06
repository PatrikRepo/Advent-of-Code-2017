#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::vector<unsigned int>> &spreadSheet)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			std::vector<unsigned int> row;
			size_t pos = 0;
			size_t endpos = 0;
			
			pos = line.find_first_of("1234567890");
			
			while(pos != std::string::npos)
			{
				endpos = line.find_first_of("	", pos);
				unsigned int number = std::stoi(line.substr(pos, endpos-pos));
				row.push_back(number);
				pos = line.find_first_of("1234567890", endpos);
			}
			spreadSheet.push_back(row);
		}
	}
	input.close();
}

uint64_t calculateChecksum(const std::vector<std::vector<unsigned int>> &spreadSheet)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<spreadSheet.size(); i++)
	{
		uint64_t largest = 0;
		uint64_t smallest = UINT64_MAX;
		for(unsigned int j=0; j<spreadSheet[i].size(); j++)
		{
			if(spreadSheet[i][j] < smallest)
			{
				smallest = spreadSheet[i][j];
			}
			if(spreadSheet[i][j] > largest)
			{
				largest = spreadSheet[i][j];
			}
		}
		result += largest - smallest;
	}
	
	return result;
}

uint64_t calculateDivisionChecksum(const std::vector<std::vector<unsigned int>> &spreadSheet)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<spreadSheet.size(); i++)
	{
		for(unsigned int j=0; j<spreadSheet[i].size()-1; j++)
		{
			for(unsigned int k=j+1; k<spreadSheet[i].size(); k++)
			{
				if(spreadSheet[i][j] % spreadSheet[i][k] == 0)
				{
					result += spreadSheet[i][j] / spreadSheet[i][k];
					j = spreadSheet[i].size();
					break;
				}
				if(spreadSheet[i][k] % spreadSheet[i][j] == 0)
				{
					result += spreadSheet[i][k] / spreadSheet[i][j];
					j = spreadSheet[i].size();
					break;
				}
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::vector<unsigned int>> spreadSheet;
	
	parseInput(spreadSheet);
	
	resultA = calculateChecksum(spreadSheet);
	resultB = calculateDivisionChecksum(spreadSheet);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
