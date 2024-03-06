#include <iostream>
#include <fstream>
#include <utility>

void parseInput(std::string &stream)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, stream);
	}
	input.close();
}

std::pair<uint64_t,uint64_t> calculateGroups(std::string &stream)
{
	std::pair<uint64_t,uint64_t> result;
	
	for(unsigned int i=0; i<stream.length()-1; i++)
	{
		if(stream[i] == '!')
		{
			stream[i+1] = ' ';
		}
	}
	
	bool garbage = false;
	for(unsigned int i=0; i<stream.length(); i++)
	{
		if(stream[i] == '>')
		{
			garbage = false;
		}
		else if(stream[i] == '<')
		{
			if(garbage)
			{
				result.second += 1;
			}
			else
			{
				garbage = true;
			}
		}
		else if(garbage && stream[i] != '!' && stream[i] != ' ')
		{
			result.second += 1;
		}
		if(garbage)
		{
			stream[i] = ' ';
		}
	}
	
	unsigned int depth = 0;
	for(unsigned int i=0; i<stream.length(); i++)
	{
		if(stream[i] == '{')
		{
			depth++;
		}
		if(stream[i] == '}')
		{
			result.first += depth;
			depth--;
		}
	}
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::string stream;
	
	parseInput(stream);
	
	result = calculateGroups(stream);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
