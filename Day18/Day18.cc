#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <queue>

void parseInput(std::vector<std::tuple<char, std::string, std::string>> &instructions, std::unordered_map<char, int64_t> &registers)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			char instruction = line[1];
			std::string first;
			std::string second;
			if(instruction == 'n' || instruction == 'c')
			{
				first += line[4];
			}
			else
			{
				size_t pos = 4;
				size_t endpos = line.find_first_of(" ", pos);
				first += line.substr(pos,endpos-pos);
				
				pos = endpos+1;
				second += line.substr(pos);
				if(first[0] > '9' && registers.count(first[0]) == 0)
				{
					registers[first[0]] = 0;
				}
				if(second[0] > '9' && registers.count(second[0]) == 0)
				{
					registers[second[0]] = 0;
				}
				
			}			
			
			instructions.push_back(std::make_tuple(instruction, first, second));
		}
	}
	input.close();
}

int64_t recoverSound(const std::vector<std::tuple<char, std::string, std::string>> &instructions, std::unordered_map<char, int64_t> registers)
{
	int64_t result = 0;
	int64_t sound = 0;
	bool firstSoundRecovered = false;
	
	for(unsigned int i=0; i<instructions.size() && i>= 0; i++)
	{
		char instruction = std::get<0>(instructions[i]);
		if(instruction == 'n')
		{
			std::string first = std::get<1>(instructions[i]);
			if(first[0] > '9')
			{
				sound = registers[first[0]];
			}
			else
			{
				sound = std::stoi(first);
			}
		}
		else if(instruction == 'e')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1] = registers[second[0]];
			}
			else
			{
				registers[reg1] = std::stoi(second);
			}
		}
		else if(instruction == 'd')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1] += registers[second[0]];
			}
			else
			{
				registers[reg1] += std::stoi(second);
			}
		}
		else if(instruction == 'u')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1] *= registers[second[0]];
			}
			else
			{
				registers[reg1] *= std::stoi(second);
			}
		}
		else if(instruction == 'o')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if(second[0] > '9')
			{
				registers[reg1] %= registers[second[0]];
			}
			else
			{
				registers[reg1] %= std::stoi(second);
			}
		}
		else if(instruction == 'c')
		{
			std::string first = std::get<1>(instructions[i]);
			if(first[0] > '9' && registers[first[0]] != 0)
			{
				if(!firstSoundRecovered)
				{
					firstSoundRecovered = true;
					result = sound;
					break;
				}
			}
			else if(std::stoi(first) != 0)
			{
				if(!firstSoundRecovered)
				{
					firstSoundRecovered = true;
					result = sound;
					break;
				}
			}
		}
		else if(instruction == 'g')
		{
			char reg1 = std::get<1>(instructions[i])[0];
			std::string second = std::get<2>(instructions[i]);
			if((reg1 > '9' && registers[reg1] != 0) || (reg1 <= '9' && reg1 != '0'))
			{
				if(second[0] > '9')
				{
					i += registers[second[0]] -1;
				}
				else
				{
					i += std::stoi(second) -1;
				}
			}
		}
	}
	
	return result;
}

uint64_t twoPrograms(const std::vector<std::tuple<char, std::string, std::string>> &instructions, const std::unordered_map<char, int64_t> &registers)
{
	int64_t result = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	std::queue<int64_t> messageQueue1;
	std::queue<int64_t> messageQueue2;
	std::unordered_map<char, int64_t> registers1 = registers;
	std::unordered_map<char, int64_t> registers2 = registers;
	registers1['p'] = 0;
	registers2['p'] = 1;

	do
	{
		while(i<instructions.size())
		{
			char instruction = std::get<0>(instructions[i]);
			if(instruction == 'n')
			{
				std::string first = std::get<1>(instructions[i]);
				if(first[0] > '9')
				{
					messageQueue2.push(registers1[first[0]]);
				}
				else
				{
					messageQueue2.push(std::stoi(first));
				}
			}
			else if(instruction == 'e')
			{
				char reg1 = std::get<1>(instructions[i])[0];
				std::string second = std::get<2>(instructions[i]);
				if(second[0] > '9')
				{
					registers1[reg1] = registers1[second[0]];
				}
				else
				{
					registers1[reg1] = std::stoi(second);
				}
			}
			else if(instruction == 'd')
			{
				char reg1 = std::get<1>(instructions[i])[0];
				std::string second = std::get<2>(instructions[i]);
				if(second[0] > '9')
				{
					registers1[reg1] += registers1[second[0]];
				}
				else
				{
					registers1[reg1] += std::stoi(second);
				}
			}
			else if(instruction == 'u')
			{
				char reg1 = std::get<1>(instructions[i])[0];
				std::string second = std::get<2>(instructions[i]);
				if(second[0] > '9')
				{
					registers1[reg1] *= registers1[second[0]];
				}
				else
				{
					registers1[reg1] *= std::stoi(second);
				}
			}
			else if(instruction == 'o')
			{
				char reg1 = std::get<1>(instructions[i])[0];
				std::string second = std::get<2>(instructions[i]);
				if(second[0] > '9')
				{
					registers1[reg1] %= registers1[second[0]];
				}
				else
				{
					registers1[reg1] %= std::stoi(second);
				}
			}
			else if(instruction == 'c')
			{
				if(!messageQueue1.empty())
				{
					char first = std::get<1>(instructions[i])[0];
					registers1[first] = messageQueue1.front();
					messageQueue1.pop();
				}
				else
				{
					break;
				}
			}
			else if(instruction == 'g')
			{
				char reg1 = std::get<1>(instructions[i])[0];
				std::string second = std::get<2>(instructions[i]);
				if((reg1 > '9' && registers1[reg1] > 0) || (reg1 <= '9' && reg1 > '0'))
				{
					if(second[0] > '9')
					{
						i += registers1[second[0]] -1;
					}
					else
					{
						i += std::stoi(second) -1;
					}
				}
			}
			i++;
		}
		while(j<instructions.size())
		{
			char instruction = std::get<0>(instructions[j]);
			if(instruction == 'n')
			{
				std::string first = std::get<1>(instructions[j]);
				if(first[0] > '9')
				{
					messageQueue1.push(registers2[first[0]]);
				}
				else
				{
					messageQueue1.push(std::stoi(first));
				}
				result++;
			}
			else if(instruction == 'e')
			{
				char reg1 = std::get<1>(instructions[j])[0];
				std::string second = std::get<2>(instructions[j]);
				if(second[0] > '9')
				{
					registers2[reg1] = registers2[second[0]];
				}
				else
				{
					registers2[reg1] = std::stoi(second);
				}
			}
			else if(instruction == 'd')
			{
				char reg1 = std::get<1>(instructions[j])[0];
				std::string second = std::get<2>(instructions[j]);
				if(second[0] > '9')
				{
					registers2[reg1] += registers2[second[0]];
				}
				else
				{
					registers2[reg1] += std::stoi(second);
				}
			}
			else if(instruction == 'u')
			{
				char reg1 = std::get<1>(instructions[j])[0];
				std::string second = std::get<2>(instructions[j]);
				if(second[0] > '9')
				{
					registers2[reg1] *= registers2[second[0]];
				}
				else
				{
					registers2[reg1] *= std::stoi(second);
				}
			}
			else if(instruction == 'o')
			{
				char reg1 = std::get<1>(instructions[j])[0];
				std::string second = std::get<2>(instructions[j]);
				if(second[0] > '9')
				{
					registers2[reg1] %= registers2[second[0]];
				}
				else
				{
					registers2[reg1] %= std::stoi(second);
				}
			}
			else if(instruction == 'c')
			{
				if(!messageQueue2.empty())
				{
					char first = std::get<1>(instructions[j])[0];
					registers2[first] = messageQueue2.front();
					messageQueue2.pop();
				}
				else
				{
					break;
				}
			}
			else if(instruction == 'g')
			{
				char reg1 = std::get<1>(instructions[j])[0];
				std::string second = std::get<2>(instructions[j]);
				if((reg1 > '9' && registers2[reg1] > 0) || (reg1 <= '9' && reg1 > '0'))
				{
					if(second[0] > '9')
					{
						j += registers2[second[0]] -1;
					}
					else
					{
						j += std::stoi(second) -1;
					}
				}
			}
			j++;
		}
	} while(!messageQueue1.empty() && i < instructions.size());
	
	return result;
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	
	std::vector<std::tuple<char, std::string, std::string>> instructions;
	std::unordered_map<char, int64_t> registers;
	
	parseInput(instructions, registers);
	
	resultA = recoverSound(instructions, registers);
	
	resultB = twoPrograms(instructions, registers);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
