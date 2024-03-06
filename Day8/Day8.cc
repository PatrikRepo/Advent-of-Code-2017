#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

struct Instruction
{
	std::string reg;
	char operation = 0;
	int value = 0;
	std::string ifReg;
	char ifOperation = 0;
	int ifValue = 0;
};

void parseInput(std::unordered_map<std::string, int> &registers, std::vector<Instruction> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			Instruction instruction;
			size_t pos = 0;
			size_t endpos = line.find_first_of(" ");
			instruction.reg = line.substr(pos, endpos-pos);
			registers[instruction.reg] = 0;
			
			instruction.operation = line[endpos+1];
			
			pos = line.find_first_of("1234567890-",endpos);
			endpos = line.find_first_of(" ", pos);
			instruction.value = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+4;
			endpos = line.find_first_of(" ", pos);
			instruction.ifReg = line.substr(pos, endpos-pos);
			
			pos = endpos+1;
			if(line[pos] == '>' && line[pos+1] == '=')
			{
				instruction.ifOperation = 'G';
			}
			else if(line[pos] == '<' && line[pos+1] == '=')
			{
				instruction.ifOperation = 'L';
			}
			else
			{
				instruction.ifOperation = line[pos];
			}
			
			pos = line.find_first_of("1234567890-",pos);
			instruction.ifValue = std::stoi(line.substr(pos));

			instructions.push_back(instruction);
		}
	}
	input.close();
}

std::pair<int64_t,int64_t> executeProgram(std::unordered_map<std::string, int> &registers, std::vector<Instruction> &instructions)
{
	std::pair<int64_t,int64_t> result;
	
	for(unsigned int i=0; i<instructions.size(); i++)
	{
		std::string ifReg = instructions[i].ifReg;
		char ifOperation = instructions[i].ifOperation;
		int ifValue = instructions[i].ifValue;
		bool executeInstruction = false;
		switch(ifOperation)
		{
			case '=':
			{
				if(registers[ifReg] == ifValue)
				{
					executeInstruction = true;
				}
				break;
			}
			case '!':
			{
				if(registers[ifReg] != ifValue)
				{
					executeInstruction = true;
				}
				break;
			}
			case '<':
			{
				if(registers[ifReg] < ifValue)
				{
					executeInstruction = true;
				}
				break;
			}
			case '>':
			{
				if(registers[ifReg] > ifValue)
				{
					executeInstruction = true;
				}
				break;
			}
			case 'G':
			{
				if(registers[ifReg] >= ifValue)
				{
					executeInstruction = true;
				}
				break;
			}
			case 'L':
			{
				if(registers[ifReg] <= ifValue)
				{
					executeInstruction = true;
				}
				break;
			}
		}
		if(executeInstruction)
		{
			std::string reg = instructions[i].reg;
			char operation = instructions[i].operation;
			int value = instructions[i].value;
			
			if(operation == 'i')
			{
				registers[reg] += value;
			}
			else
			{
				registers[reg] -= value;
			}
			if(result.second < registers[reg])
			{
				result.second = registers[reg];
			}
		}
	}
	
	for(auto it=registers.begin(); it!=registers.end(); it++)
	{
		if(result.first < it->second)
		{
			result.first = it->second;
		}
	}
	
	return result;
}

int main()
{
	std::pair<int64_t,int64_t> result;
	std::unordered_map<std::string, int> registers;
	std::vector<Instruction> instructions;
	
	parseInput(registers, instructions);
	
	result = executeProgram(registers, instructions);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
