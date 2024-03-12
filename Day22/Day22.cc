#include <iostream>
#include <fstream>
#include <vector>

enum Direction {UP, RIGHT, DOWN, LEFT};

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

uint64_t infect(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	char bigMap[1001][1001] = {'.'};
	int direction = Direction::UP;
	size_t x = 500;
	size_t y = 500;
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			bigMap[500+i-(map.size()/2)][500+j-(map[0].length()/2)] = map[i][j];
		}
	}
	
	for(unsigned int i=0; i<10000; i++)
	{
		if(bigMap[y][x] == '#')
		{
			direction = (direction+1)%4;
			bigMap[y][x] = '.';
		}
		else
		{
			direction = (direction+3)%4;
			bigMap[y][x] = '#';
			result++;
		}
		
		switch(direction)
		{
			case Direction::UP:
			{
				y--;
				break;
			}
			case Direction::RIGHT:
			{
				x++;
				break;
			}
			case Direction::DOWN:
			{
				y++;
				break;
			}
			case Direction::LEFT:
			{
				x--;
				break;
			}
		}
	}
	
	return result;
}

uint64_t weakenAndInfect(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	std::vector<std::vector<char>> bigMap;
	std::vector<char> charRow;
	for(int i=0; i<10001; i++)
	{
		charRow.push_back('.');
	}
	for(int i=0; i<10001; i++)
	{
		bigMap.push_back(charRow);
	}
	
	int direction = Direction::UP;
	size_t x = 5000;
	size_t y = 5000;
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			bigMap[5000+i-(map.size()/2)][5000+j-(map[0].length()/2)] = map[i][j];
		}
	}
	
	for(unsigned int i=0; i<10000000; i++)
	{
		if(bigMap[y][x] == '#')
		{
			direction = (direction+1)%4;
			bigMap[y][x] = 'F';
		}
		else if(bigMap[y][x] == '.')
		{
			direction = (direction+3)%4;
			bigMap[y][x] = 'W';
		}
		else if(bigMap[y][x] == 'W')
		{
			bigMap[y][x] = '#';
			result++;
		}
		else
		{
			direction = (direction+2)%4;
			bigMap[y][x] = '.';
		}
		
		switch(direction)
		{
			case Direction::UP:
			{
				y--;
				break;
			}
			case Direction::RIGHT:
			{
				x++;
				break;
			}
			case Direction::DOWN:
			{
				y++;
				break;
			}
			case Direction::LEFT:
			{
				x--;
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
	std::vector<std::string> map;
	
	parseInput(map);

	resultA = infect(map);
	
	resultB = weakenAndInfect(map);

	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
