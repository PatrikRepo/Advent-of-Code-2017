#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<std::pair<unsigned int, unsigned int>> &parts)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			size_t pos = line.find_first_of("/");
			unsigned int first = std::stoi(line.substr(0,pos));
			unsigned int second = std::stoi(line.substr(pos+1));
			
			parts.push_back(std::make_pair(first, second));
		}
	}
	input.close();
}

uint64_t buildBridge(std::vector<std::pair<unsigned int,unsigned int>> &parts, const unsigned int pins)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<parts.size(); i++)
	{
		bool found = false;
		unsigned int newPins = 0;
		if(parts[i].first == pins)
		{
			newPins = parts[i].second;
			found = true;
		}
		else if(parts[i].second == pins)
		{
			newPins = parts[i].first;
			found = true;
		}
		if(found)
		{
			auto newParts = parts;
			newParts.erase(newParts.begin() + i);
			uint64_t newResult = buildBridge(newParts, newPins) + pins;
			if(newResult > result)
			{
				result = newResult;
			}
		}
	}
	
	result += pins;
	
	return result;
}


std::pair<uint64_t,uint64_t> buildLongBridge(std::vector<std::pair<unsigned int,unsigned int>> &parts, const unsigned int pins, const unsigned int partResult, const unsigned int length, unsigned int &maxLength)
{
	std::pair<uint64_t,uint64_t> result;
	if(length > maxLength)
	{
		maxLength = length;
	}
	
	for(unsigned int i=0; i<parts.size(); i++)
	{
		bool found = false;
		unsigned int newPins = 0;
		if(parts[i].first == pins)
		{
			newPins = parts[i].second;
			found = true;
		}
		else if(parts[i].second == pins)
		{
			newPins = parts[i].first;
			found = true;
		}
		if(found)
		{
			auto newParts = parts;
			newParts.erase(newParts.begin() + i);
			std::pair<uint64_t,uint64_t> newResult = buildLongBridge(newParts, newPins, partResult + (pins*2), length+1, maxLength);
			if(result.second < newResult.second || (newResult.first > result.first && newResult.second == result.second))
			{
				result.first = newResult.first;
				result.second = newResult.second;
			}
		}
	}
	
	if(length == maxLength)
	{
		result.first = partResult + pins;
		result.second = maxLength;
	}
	
	return result;
}


int main()
{
	uint64_t resultA = 0;
	std::pair<uint64_t,uint64_t> resultB;
	std::vector<std::pair<unsigned int,unsigned int>> parts;
	
	parseInput(parts);
	
	resultA = buildBridge(parts, 0);
	
	unsigned int maxLength = 0;
	resultB = buildLongBridge(parts, 0, 0, 0, maxLength);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB.first << std::endl;
	
	return 0;
}
