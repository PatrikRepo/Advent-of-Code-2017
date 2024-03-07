#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<char> &stepsTaken)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		
		size_t pos = 0;
		
		while(pos < line.length())
		{
			char step = line[pos];
			if(pos < line.length()-1 && line[pos+1] != ',')
			{
				if(step == 'n')
				{
					if(line[pos+1] == 'e')
					{
						step = 'E';
					}
					else
					{
						step = 'W';
					}
				}
				else
				{
					if(line[pos+1] == 'e')
					{
						step = 'e';
					}
					else
					{
						step = 'w';
					}
				}
			
				pos += 3;
			}
			else
			{
				pos += 2;
			}
			stepsTaken.push_back(step);
			
		}
	}
	input.close();
}

std::pair<uint64_t,uint64_t> countSteps(const std::vector<char> &stepsTaken)
{
	std::pair<uint64_t,uint64_t> result;
	
	int posX = 0;
	int posY = 0;
	bool halfStep = false;
	
	for(unsigned int i=0; i<stepsTaken.size(); i++)
	{
		switch(stepsTaken[i])
		{
			case 'n':
			{
				posY++;
				break;
			}
			case 's':
			{
				posY--;
				break;
			}
			case ('E'):
			{
				posX++;
				if(halfStep)
				{
					posY++;
					halfStep = false;
				}
				else
				{
					halfStep = true;
				}
				break;
			}
			case ('W'):
			{
				posX--;
				if(halfStep)
				{
					posY++;
					halfStep = false;
				}
				else
				{
					halfStep = true;
				}
				break;
			}
			case ('e'):
			{
				posX++;
				if(halfStep)
				{
					halfStep = false;
				}
				else
				{
					posY--;
					halfStep = true;
				}
				break;
			}
			case ('w'):
			{
				posX--;
				if(halfStep)
				{
					halfStep = false;
				}
				else
				{
					posY--;
					halfStep = true;
				}
				break;
			}
		}
		uint64_t newDistance = abs(posX);
		if(abs(posY) > abs(posX)/2)
		{
			newDistance += abs(posY) - abs(posX)/2;
			if(posY < 0 && halfStep)
			{
				newDistance--;
			}
		}
		if(newDistance > result.second)
		{
			result.second = newDistance;
		}
	}
	
	result.first = abs(posX);
	if(abs(posY) > abs(posX)/2)
	{
		result.first += abs(posY) - abs(posX)/2;
	}
	if(posY < 0 && halfStep)
	{
		result.first--;
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::vector<char> stepsTaken;
	
	parseInput(stepsTaken);

	result = countSteps(stepsTaken);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
