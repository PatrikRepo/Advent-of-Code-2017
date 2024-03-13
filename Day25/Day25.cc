#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct State
{
	char id = 0;
	unsigned int zeroWrite = 0;
	unsigned int oneWrite = 0;
	char zeroMove = 0;
	char oneMove = 0;
	char zeroState = 0;
	char oneState = 0;
};

void parseInput(char &firstState, unsigned int &steps, std::unordered_map<char,State> &states)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
		size_t pos = line.find_first_of(".")-1;
		firstState = line[pos];
		
		getline(input,line);
		pos = line.find_first_of("1234567890");
		size_t endpos = line.find_first_of(" ", pos);
		steps = std::stoi(line.substr(pos,endpos-pos));
		
		while(getline(input,line))
		{
			getline(input,line);
			
			State state;
			state.id = line[9];
			
			getline(input,line);
			getline(input,line);
			state.zeroWrite = line[22] - '0';
			
			getline(input,line);
			state.zeroMove = line[27];
			
			getline(input,line);
			state.zeroState = line[26];
			
			getline(input,line);
			getline(input,line);
			state.oneWrite = line[22] - '0';
			
			getline(input,line);
			state.oneMove = line[27];
			
			getline(input,line);
			state.oneState = line[26];
			
			states[state.id] = state;
		}
	}
	input.close();
}

uint64_t getChecksum(const char firstState, const unsigned int steps, std::unordered_map<char,State> &states)
{
	uint64_t result = 0;
	char state = firstState;
	std::vector<unsigned int> tape; 
	tape.push_back(0);
	auto it = tape.begin();
	
	for(unsigned int i=0; i<steps; i++)
	{
		if(*it == 0)
		{
			*it = states[state].zeroWrite;
			if(states[state].zeroMove == 'r')
			{
				if(it+1 == tape.end())
				{
					tape.push_back(0);
					it = tape.end()-1;
				}
				else
				{
					it++;
				}
			}
			else
			{
				if(it == tape.begin())
				{
					tape.insert(tape.begin(), 0);
					it = tape.begin();
				}
				else
				{
					it--;
				}
			}
			state = states[state].zeroState;
		}
		else
		{
			*it = states[state].oneWrite;
			if(states[state].oneMove == 'r')
			{
				if(it+1 == tape.end())
				{
					tape.push_back(0);
					it = tape.end()-1;
				}
				else
				{
					it++;
				}
			}
			else
			{
				if(it == tape.begin())
				{
					tape.insert(tape.begin(), 0);
					it = tape.begin();
				}
				else
				{
					it--;
				}
			}
			state = states[state].oneState;
		}
	}
	
	for(it=tape.begin(); it!=tape.end(); it++)
	{
		if(*it == 1)
		{
			result++;
		}
	}
	
	return result;
}

int main()
{
	uint64_t result = 0;
	char firstState = 0;
	unsigned int steps = 0;
	std::unordered_map<char,State> states;
	
	parseInput(firstState, steps, states);
	
	result = getChecksum(firstState, steps, states);
	
	std::cout << "result: " << result << std::endl;
	
	return 0;
}
