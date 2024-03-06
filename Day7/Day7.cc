#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Program
{
	std::string name;
	std::string parent = "";
	std::vector<std::string> children;
	unsigned int weight;
};


void parseInput(std::unordered_map<std::string, Program> &programs)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = 0;
			size_t endpos = line.find_first_of(" ");
			Program program;
			std::string name = line.substr(pos, endpos);
			program.name = name;
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(")", pos);
			program.weight = std::stoi(line.substr(pos, endpos-pos));
			
			bool childrenProcessed = true;
			pos = line.find_first_of(">", endpos);
			if(pos != std::string::npos)
			{
				childrenProcessed = false;
				pos += 2;
			}
			
			while(!childrenProcessed)
			{
				endpos = line.find_first_of(",",pos);
				std::string child;
				if(endpos != std::string::npos)
				{
					child = line.substr(pos, endpos-pos);
					pos = endpos +2;
				}
				else
				{
					child = line.substr(pos);
					childrenProcessed = true;
				}
				program.children.push_back(child);
			}
			
			programs[name] = program;
		}
	}
	input.close();
}

void findParents(std::unordered_map<std::string, Program> &programs)
{
	for(auto it=programs.begin(); it!=programs.end(); it++)
	{
		for(unsigned int j=0; j<it->second.children.size(); j++)
		{
			programs[it->second.children[j]].parent = it->second.name;
		}
	}
}

std::string findBase(std::unordered_map<std::string, Program> &programs)
{
	std::string result;
	bool foundBase = false;
	Program * program = &(programs.begin()->second);
	std::string parent;
	while(!foundBase)
	{
		parent = program->parent;
		if(parent != "")
		{
			program = &programs[parent];
		}
		else
		{
			foundBase = true;
			result = program->name;
		}
	}
	
	return result;
}

uint64_t findWeight(std::unordered_map<std::string, Program> &programs, std::string programName, uint64_t &childWeight, uint64_t &totalWeight)
{
	uint64_t result = 0;
	Program * program = &programs[programName];
	
	if(program->children.size() != 0)
	{
		std::vector<std::pair<uint64_t,uint64_t>> weights;
		for(unsigned int i=0; i<program->children.size(); i++)
		{
			uint64_t newChildWeight = 0;
			uint64_t newTotalWeight = 0;
			result = findWeight(programs, program->children[i], newChildWeight, newTotalWeight);
			if(result != 0)
			{
				break;
			}
			else
			{
				weights.push_back(std::make_pair(newTotalWeight, newChildWeight));
			}
		}
		if(result == 0)
		{
			bool foundImbalance = false;
			unsigned int index = 0;
			for(unsigned int i=1; i<weights.size(); i++)
			{
				if(weights[0].first != weights[i].first)
				{
					foundImbalance = true;
					index = i;
					break;
				}
			}
			if(foundImbalance)
			{
				if(index == 1)
				{
					if(weights[0].first == weights[2].first)
					{
						result = weights[1].second + weights[0].first - weights[1].first;
					}
					else
					{
						result = weights[0].second + weights[1].first - weights[0].first;
					}
				}
				else
				{
					result = weights[index].second + weights[1].second - weights[index].second;
				}
			}
			else
			{
				childWeight = program->weight;
				totalWeight = (weights[0].first*weights.size()) + program->weight;
			}
		}
	}
	else
	{
		childWeight = program->weight;
		totalWeight = program->weight;
	}
	
	return result;
} 

uint64_t findWeight(std::unordered_map<std::string, Program> &programs, std::string base)
{
	uint64_t result = 0;
	
	uint64_t childWeight = 0;
	uint64_t totalWeight = 0;
	result = findWeight(programs, base, childWeight, totalWeight);
	
	return result;
}

int main()
{
	std::string resultA;
	uint64_t resultB = 0;
	std::unordered_map<std::string, Program> programs;
	
	parseInput(programs);
	findParents(programs);
	
	resultA = findBase(programs);
	resultB = findWeight(programs, resultA);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
