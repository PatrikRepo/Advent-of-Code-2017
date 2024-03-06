#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

void parseInput(std::vector<std::vector<std::string>> &passPhrases)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			std::vector<std::string> passPhrase;
			size_t pos = 0;
			size_t endpos = line.find_first_of(" ");
			std::string word;
			while(endpos != std::string::npos)
			{
				word = line.substr(pos, endpos-pos);
				passPhrase.push_back(word);
				pos = endpos + 1;
				endpos = line.find_first_of(" ", pos);
			}
			word = line.substr(pos);
			passPhrase.push_back(word);
			passPhrases.push_back(passPhrase);
		}
	}
	input.close();
}

uint64_t calculateValidPassPhrases(const std::vector<std::vector<std::string>> &passPhrases, const bool anagrams)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<passPhrases.size(); i++)
	{
		std::unordered_map<std::string, int> words;
		bool valid = true;
		for(unsigned int j=0; j<passPhrases[i].size(); j++)
		{
			std::string word = passPhrases[i][j];
			if(anagrams)
			{
				std::sort(word.begin(), word.end());
			}
			if(words.count(word))
			{
				valid = false;
				break;
			}
			words[word] += 1;
		}
		if(valid)
		{
			result++;
		}
	}
	
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::vector<std::string>> passPhrases;
	
	parseInput(passPhrases);
	
	resultA = calculateValidPassPhrases(passPhrases, false);
	resultB = calculateValidPassPhrases(passPhrases, true);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
