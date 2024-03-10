#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			map.push_back(line);
		}
	}
	input.close();
}

std::pair<std::string,uint64_t> traverseMap(const std::vector<std::string> map)
{
	std::pair<std::string,uint64_t> result;
	size_t posX = 0;
	size_t posY = 0;
	char direction = 'd';
	bool done = false;
	for(unsigned int i=0; i<map[0].length(); i++)
	{
		if(map[0][i] == '|')
		{
			posX = i;
			break;
		}
	}
	
	while(!done)
	{
		result.second++;
		if(map[posY][posX] >= 'A' && map[posY][posX] <= 'Z')
		{
			result.first += map[posY][posX];
		}
		switch(direction)
		{
			case 'd':
			{
				if(map[posY+1][posX] != ' ')
				{
					posY++;
				} 
				else if(map[posY][posX-1] != '|' && map[posY][posX-1] != ' ')
				{
					posX--;
					direction = 'l';
				}
				else if(map[posY][posX+1] != '|' && map[posY][posX+1] != ' ')
				{
					posX++;
					direction = 'r';
				}
				else
				{
					done = true;
				}
				break;
			}
			case 'l':
			{
				if(map[posY][posX-1] != ' ')
				{
					posX--;
				} 
				else if(map[posY-1][posX] != '-' && map[posY-1][posX] != ' ')
				{
					posY--;
					direction = 'u';
				}
				else if(map[posY+1][posX] != '-' && map[posY+1][posX] != ' ')
				{
					posY++;
					direction = 'd';
				}
				else
				{
					done = true;
				}
				break;
			}
			case 'u':
			{
				if(map[posY-1][posX] != ' ')
				{
					posY--;
				} 
				else if(map[posY][posX-1] != '|' && map[posY][posX-1] != ' ')
				{
					posX--;
					direction = 'l';
				}
				else if(map[posY][posX+1] != '|' && map[posY][posX+1] != ' ')
				{
					posX++;
					direction = 'r';
				}
				else
				{
					done = true;
				}
				break;
			}
			case 'r':
			{
				if(map[posY][posX+1] != ' ')
				{
					posX++;
				} 
				else if(map[posY-1][posX] != '-' && map[posY-1][posX] != ' ')
				{
					posY--;
					direction = 'u';
				}
				else if(map[posY+1][posX] != '-' && map[posY+1][posX] != ' ')
				{
					posY++;
					direction = 'd';
				}
				else
				{
					done = true;
				}
				break;
			}
		}
	}
	
	return result;
}	

int main()
{
	std::pair<std::string,uint64_t> result;
	std::vector<std::string> map;
	
	parseInput(map);
	
	result = traverseMap(map);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;

	return 0;
}
