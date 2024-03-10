#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(unsigned int &steps)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		steps = std::stoi(line);
	}
	input.close();
}

std::pair<uint64_t,uint64_t> calculateSpinlockEnd(const unsigned int steps)
{
	std::pair<uint64_t,uint64_t> result;
	std::vector<unsigned int> spinlock;
	spinlock.push_back(0);
	spinlock.push_back(1);
	unsigned int pos = 1;
	
	for(int i=2; i<=2017; i++)
	{
		pos = (pos+steps)%spinlock.size()+1;
		spinlock.insert(spinlock.begin()+pos, i);
	}
	result.first = spinlock[pos+1];
	
	pos = 1;
	for(int i=2; i<=50000000; i++)
	{
		pos = (pos+steps)%i+1;
		if(pos == 1)
		{
			result.second = i;
		}
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	unsigned int steps = 0;
	
	parseInput(steps);

	result = calculateSpinlockEnd(steps);
	
	std::cout << "resultA: " << result.first << '\n';
	std::cout << "resultB: " << result.second << std::endl;
	
	return 0;
}
