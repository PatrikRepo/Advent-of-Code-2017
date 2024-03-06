#include <iostream>
#include <fstream>

void parseInput(std::string &captcha)
{
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, captcha);
	}
	input.close();
	
}


uint64_t solveCaptcha(const std::string &captcha)
{
	uint64_t result = 0;
	
	for(unsigned int i=0; i<captcha.length()-1; i++)
	{
		if(captcha[i] == captcha[i+1])
		{
			result += captcha[i] - '0';
		}
	}
	if(captcha[0] == captcha[captcha.length()-1])
	{
		result += captcha[0] - '0';
	}
	return result;
}

uint64_t solveOtherCaptcha(const std::string &captcha)
{
	uint64_t result = 0;
	unsigned int halfWay = captcha.length()/2;
	for(unsigned int i=0; i<captcha.length(); i++)
	{
		if(captcha[i] == captcha[(i+halfWay)%captcha.length()])
		{
			result += captcha[i] - '0';
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string captcha;
	
	parseInput(captcha);
	
	resultA = solveCaptcha(captcha);
	resultB = solveOtherCaptcha(captcha);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
