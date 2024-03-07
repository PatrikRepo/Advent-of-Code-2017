#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>

struct Program
{
	unsigned int id = 0;
	int parent = -1;
	std::vector<unsigned int> communicatesWith;
};

void parseInput(std::vector<Program> &programs)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			Program program;
			size_t pos = 0;
			size_t endpos = line.find_first_of(" ");
			unsigned int programId = std::stoi(line.substr(0, endpos));
			program.id = programId;
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(",", pos);
			while(endpos != std::string::npos)
			{
				programId = std::stoi(line.substr(pos, endpos-pos));
				program.communicatesWith.push_back(programId);
				pos = line.find_first_of("1234567890", endpos);
				endpos = line.find_first_of(",", pos);
			}
			programId = std::stoi(line.substr(pos));
			program.communicatesWith.push_back(programId);
			
			programs.push_back(program);
		}
	}
	input.close();
}

void setParent(std::vector<Program> &programs, const unsigned int programId, const int parentId)
{
	Program * program = &programs[programId];
	if(program->parent == -1)
	{
		program->parent = parentId;
		for(unsigned int i=0; i<program->communicatesWith.size(); i++)
		{
			setParent(programs, program->communicatesWith[i], parentId);
		}
	}
}

void findParents(std::vector<Program> &programs)
{
	for(unsigned int i=0; i<programs.size(); i++)
	{
		if(programs[i].parent == -1)
		{
			setParent(programs, i, programs[i].id);
		}
	}
}

std::pair<uint64_t,uint64_t> findGroups(const std::vector<Program> &programs)
{
	std::pair<uint64_t,uint64_t> result;
	std::unordered_map<unsigned int, unsigned int> groups;
	
	for(unsigned int i=0; i<programs.size(); i++)
	{
		groups[programs[i].parent] = 0;
		if(programs[i].parent == 0)
		{	
			result.first += 1;
		}
	}
	result.second = groups.size();
	
	return result;
}

int main()
{
	std::pair<uint64_t, uint64_t> result;
	std::vector<Program> programs;
	
	parseInput(programs);
	findParents(programs);
	
	result = findGroups(programs);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
