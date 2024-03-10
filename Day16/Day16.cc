#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>

void parseInput(std::vector<std::tuple<char,int,int>> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		{
			size_t pos = 0;
			size_t endpos = 0;
			while(pos < line.length())
			{
				char instruction = line[pos];
				int first = 0;
				int second = 0;
				switch(instruction)
				{
					case 's':
					{
						pos++;
						endpos = line.find_first_of(",", pos);
						if(endpos == std::string::npos)
						{
							endpos = line.length();
						}
						first = std::stoi(line.substr(pos,endpos-pos));
						pos = endpos+1;
						break;
					}
					case 'x':
					{
						pos++;
						endpos = line.find_first_of("/", pos);
						first = std::stoi(line.substr(pos,endpos-pos));
						pos = endpos+1;
						endpos = line.find_first_of(",", pos);
						if(endpos == std::string::npos)
						{
							endpos = line.length();
						}
						second = std::stoi(line.substr(pos,endpos-pos));
						pos = endpos+1;
						break;
					}
					case 'p':
					{
						first = line[pos+1];
						second = line[pos+3];
						pos += 5;
						break;
					}
				}
				instructions.push_back(std::make_tuple(instruction, first, second));
			}
		}
	}
	input.close();
}

std::string dance(const std::string &dancers, const std::vector<std::tuple<char,int,int>> &instructions)
{
	std::string result = dancers;
	
	for(auto it=instructions.begin(); it!=instructions.end(); it++)
	{
		switch(std::get<0>(*it))
		{
			case 's':
			{
				unsigned int steps = std::get<1>(*it);
				std::string newString = result;
				for(unsigned int i=0; i<result.length(); i++)
				{
					result[(i+steps)%result.length()] = newString[i];
				}
				break;
			}
			case 'x':
			{
				int first = std::get<1>(*it);
				int second = std::get<2>(*it);
				char swapped = result[first];
				result[first] = result[second];
				result[second] = swapped;
				break;
			}
			case 'p':
			{
				char firstLetter = std::get<1>(*it);
				char secondLetter = std::get<2>(*it);
				int first = result.find_first_of(firstLetter);
				int second = result.find_first_of(secondLetter);
				char swapped = result[first];
				result[first] = result[second];
				result[second] = swapped;
				break;
			}
		}
	}
	
	return result;
}

std::string danceAgain(const std::string &dancers, const std::vector<std::tuple<char,int,int>> &instructions)
{
	std::string result = dancers;
	std::unordered_map<std::string,unsigned int> dances;
	dances[dancers] += 1;
	unsigned int loopSize = 0;
	for(int i=1; i<1000; i++)
	{
		result = dance(result, instructions);
		if(dances.count(result))
		{
			loopSize = i;
			break;
		}
		else
		{
			dances[result] += 1;
		}
	}
	int offset = 1000000000%loopSize;
	
	for(int i=0; i<offset; i++)
	{
		result = dance(result, instructions);
	}
	
	return result;
}

int main()
{
	std::string resultA;
	std::string resultB;
	std::vector<std::tuple<char,int,int>> instructions;
	std::string dancers = "abcdefghijklmnop";
	
	parseInput(instructions);

	resultA = dance(dancers, instructions);
	
	resultB = danceAgain(dancers, instructions);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
