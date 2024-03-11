#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

void parseInput(std::unordered_map<std::string, std::vector<std::string>> &rules)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			std::vector<std::vector<char>> ruleInput;
			std::vector<char> ruleInputLine;
			size_t pos = 0;
			while(line[pos] != ' ')
			{
				if(line[pos] == '/')
				{
					ruleInput.push_back(ruleInputLine);
					ruleInputLine.clear();
				}
				else
				{
					ruleInputLine.push_back(line[pos]);
				}
				pos++;
			}
			ruleInput.push_back(ruleInputLine);
			
			std::vector<std::string> ruleOutput;
			pos = line.find_first_of(">", pos) +2;
			std::string ruleLine;
			while(pos < line.length())
			{
				if(line[pos] == '/')
				{
					ruleOutput.push_back(ruleLine);
					ruleLine = "";
				}
				else
				{
					ruleLine += line[pos];
				}
				pos++;
			}
			ruleOutput.push_back(ruleLine);
			
			ruleLine = "";
			for(unsigned int i=0; i<ruleInput.size(); i++)
			{
				for(unsigned int j=0; j<ruleInput[0].size(); j++)
				{
					ruleLine += ruleInput[i][j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int i=0; i<ruleInput.size(); i++)
			{
				for(unsigned int j=0; j<ruleInput[0].size(); j++)
				{
					ruleLine += ruleInput[i][ruleInput.size() - 1 - j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int i=0; i<ruleInput.size(); i++)
			{
				for(unsigned int j=0; j<ruleInput[0].size(); j++)
				{
					ruleLine += ruleInput[ruleInput.size() - 1 - i][j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int i=0; i<ruleInput.size(); i++)
			{
				for(unsigned int j=0; j<ruleInput[0].size(); j++)
				{
					ruleLine += ruleInput[ruleInput.size() - 1 - i][ruleInput.size() - 1 - j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int j=0; j<ruleInput[0].size(); j++)
			{
				for(unsigned int i=0; i<ruleInput.size(); i++)
				{
					ruleLine += ruleInput[i][j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int j=0; j<ruleInput[0].size(); j++)
			{
				for(unsigned int i=0; i<ruleInput.size(); i++)
				{
					ruleLine += ruleInput[i][ruleInput.size() - 1 - j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int j=0; j<ruleInput[0].size(); j++)
			{
				for(unsigned int i=0; i<ruleInput.size(); i++)
				{
					ruleLine += ruleInput[ruleInput.size() - 1 - i][j];
				}
			}
			rules[ruleLine] = ruleOutput;
			
			ruleLine = "";
			for(unsigned int j=0; j<ruleInput[0].size(); j++)
			{
				for(unsigned int i=0; i<ruleInput.size(); i++)
				{
					ruleLine += ruleInput[ruleInput.size() - 1 - i][ruleInput.size() - 1 - j];
				}
			}
			rules[ruleLine] = ruleOutput;
		}
	}
	input.close();
}

void expandImage(std::unordered_map<std::string,std::vector<std::string>> &rules, std::vector<std::string> &image, const unsigned int times)
{
	for(unsigned int i=0; i<times; i++)
	{
		std::vector<std::string> newImage;
		if(image.size() % 2 == 0)
		{
			for(unsigned int j=0; j<image.size() + image.size()/2; j++)
			{
				newImage.push_back("");
			}
			for(unsigned int j=0; j<image.size()/2; j++)
			{
				for(unsigned int k=0; k<image.size()/2; k++)
				{
					std::string square;
					square += image[j*2][k*2];
					square += image[j*2][(k*2)+1];
					square += image[(j*2)+1][k*2];
					square += image[(j*2)+1][(k*2)+1];
					std::vector<std::string> newSquare = rules[square];
					for(unsigned int r=0; r<newSquare.size(); r++)
					{
						newImage[(j*3)+r] += newSquare[r];
					}
				}
			}
		}
		else
		{
			for(unsigned int j=0; j<image.size() + image.size()/3; j++)
			{
				newImage.push_back("");
			}
			for(unsigned int j=0; j<image.size()/3; j++)
			{
				for(unsigned int k=0; k<image.size()/3; k++)
				{
					std::string square;
					square += image[j*3][k*3];
					square += image[j*3][(k*3)+1];
					square += image[j*3][(k*3)+2];
					square += image[(j*3)+1][k*3];
					square += image[(j*3)+1][(k*3)+1];
					square += image[(j*3)+1][(k*3)+2];
					square += image[(j*3)+2][k*3];
					square += image[(j*3)+2][(k*3)+1];
					square += image[(j*3)+2][(k*3)+2];
					std::vector<std::string> newSquare = rules[square];
					for(unsigned int r=0; r<newSquare.size(); r++)
					{
						newImage[(j*4)+r] += newSquare[r];
					}
				}
			}
		}
		image = newImage;
	}	
}

uint64_t countTurnedOn(const std::vector<std::string> &image)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<image.size(); i++)
	{
		for(unsigned int j=0; j<image[0].length(); j++)
		{
			if(image[i][j] == '#')
			{
				result++;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::unordered_map<std::string,std::vector<std::string>> rules;
	std::vector<std::string> image = {".#.","..#","###"};
	
	parseInput(rules);
	expandImage(rules, image, 5);

	resultA = countTurnedOn(image);
	
	expandImage(rules, image, 13);
	
	resultB = countTurnedOn(image);

	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
