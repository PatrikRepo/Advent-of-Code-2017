#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

void parseInput(std::vector<std::tuple<char, std::string, std::string>> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			char instruction = line[2];
			std::string first;
			std::string second;
			
			size_t pos = 4;
			size_t endpos = line.find_first_of(" ", pos);
			first += line.substr(pos,endpos-pos);
			
			pos = endpos+1;
			second += line.substr(pos);
			
			instructions.push_back(std::make_tuple(instruction, first, second));
		}
	}
	input.close();
}

uint64_t executeProgram(const std::vector<std::tuple<char, std::string, std::string>> &instructions, int64_t registers[8])
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<instructions.size(); i++)
	{
		char instruction = std::get<0>(instructions[i]);
		
		if(instruction == 't')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1-'a'] = registers[second[0]-'a'];
			}
			else
			{
				registers[reg1-'a'] = std::stoi(second);
			}
		}
		else if(instruction == 'b')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1-'a'] -= registers[second[0]-'a'];
			}
			else
			{
				registers[reg1-'a'] -= std::stoi(second);
			}
		}
		else if(instruction == 'l')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1-'a'] *= registers[second[0]-'a'];
			}
			else
			{
				registers[reg1-'a'] *= std::stoi(second);
			}
			result++;
		}
		else if(instruction == 'z')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			if((reg1 > '9' && registers[reg1-'a'] != 0) || (reg1 != '0' && reg1 <= '9'))
			{
				std::string second = std::get<2>(instructions[i]);
				if(second[0] > '9')
				{
					i += registers[second[0]-'a']-1;
				}
				else
				{
					i += std::stoi(second)-1;
				}
			}
		}
	}
	
	return result;
}

uint64_t findPrimes(const std::vector<std::tuple<char, std::string, std::string>> &instructions)
{
	uint64_t result = 0;
	std::vector<int> primes;
	int from = std::stoi(std::get<2>(instructions[0]));
	from *= std::stoi(std::get<2>(instructions[4]));
	from -= std::stoi(std::get<2>(instructions[5]));
	int to = from - std::stoi(std::get<2>(instructions[7]));
	
	for(int i=from; i<=to; i+=17)
	{
		for(int j=2; j*j<i; j++)
		{
			if(i%j == 0)
			{
				result++;
				break;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::tuple<char, std::string, std::string>> instructions;
	int64_t registers[8] = {0};
	
	parseInput(instructions);
	
	resultA = executeProgram(instructions, registers);
	
	resultB = findPrimes(instructions);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
