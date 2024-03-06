#include <iostream>
#include <fstream>

void parseInput(unsigned int &dataSquare)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		dataSquare = std::stoi(line);
	}
	input.close();
	
}


uint64_t countSteps(const unsigned int dataSquare)
{
	uint64_t result = 0;
	
	unsigned int highest = 1;
	unsigned int layer= 0;
	unsigned int wallSize = 1;
	bool foundLayer = false;
	
	while(!foundLayer)
	{
		unsigned int newHighest = highest + wallSize*4 + 4;
		if(newHighest > dataSquare)
		{
			foundLayer = true;
			break;
		}
		highest = newHighest;
		wallSize += 2;
		layer++;
	}
	
	int posY = +layer;
	int posX = layer;
	
	highest += 1;
	posX++;
	
	if(highest == dataSquare)
	{
		goto calculateResult;
	}
	highest += wallSize;
	posY -= wallSize;
	if(highest >= dataSquare)
	{
		posY += highest-dataSquare;
		goto calculateResult;
	}

	highest += wallSize+1;
	posX -= wallSize+1;
	
	if(highest >= dataSquare)
	{
		posX += highest-dataSquare;
		goto calculateResult;
	}
	
	highest += wallSize+1;
	posY += wallSize+1;
	
	if(highest >= dataSquare)
	{
		posY -= highest-dataSquare;
		goto calculateResult;
	}	
	
	highest += wallSize+1;
	posX += wallSize+1;
	posX -= highest-dataSquare;
	
	calculateResult:;
	
	result = abs(posX) + abs(posY);

	return result;
}

unsigned int sumAllNeighbors(const unsigned int map[100][100], const size_t posX, const size_t posY)
{
	unsigned int result = 0;
	
	result += map[posY-1][posX-1];
	result += map[posY-1][posX];
	result += map[posY-1][posX+1];
	result += map[posY][posX-1];
	result += map[posY][posX+1];
	result += map[posY+1][posX-1];
	result += map[posY+1][posX];
	result += map[posY+1][posX+1];
	
	return result;
}

uint64_t findFirstSquareHigher(const unsigned int dataSquare)
{
	uint64_t result = 0;
	size_t posX = 51;
	size_t posY = 50;
	char direction = 'U';
	unsigned int map[100][100] = {0};
	
	map[50][50] = 1;
	
	while(result == 0)
	{
		map[posY][posX] = sumAllNeighbors(map, posX, posY);
		if(map[posY][posX] > dataSquare)
		{
			result = map[posY][posX];
		}
		else
		{
			switch(direction)
			{
				case 'U':
				{
					if(map[posY][posX-1] == 0)
					{
						direction = 'L';
						posX--;
					}
					else
					{
						posY--;
					}
					break;
				}
				case 'L':
				{
					if(map[posY+1][posX] == 0)
					{
						direction = 'D';
						posY++;
					}
					else
					{
						posX--;
					}
					break;
				}
				case 'D':
				{
					if(map[posY][posX+1] == 0)
					{
						direction = 'R';
						posX++;
					}
					else
					{
						posY++;
					}
					break;
				}
				case 'R':
				{
					if(map[posY-1][posX] == 0)
					{
						direction = 'U';
						posY--;
					}
					else
					{
						posX++;
					}
					break;
				}
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	unsigned int dataSquare;
	
	parseInput(dataSquare);
	
	resultA = countSteps(dataSquare);
	resultB = findFirstSquareHigher(dataSquare);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
