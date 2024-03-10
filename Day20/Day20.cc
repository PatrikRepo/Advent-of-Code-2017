#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>

struct Particle
{
	int64_t pX = 0;
	int64_t pY = 0;
	int64_t pZ = 0;
	int64_t vX = 0;
	int64_t vY = 0;
	int64_t vZ = 0;
	int64_t aX = 0;
	int64_t aY = 0;
	int64_t aZ = 0;
	
	void update()
	{
		vX += aX;
		vY += aY;
		vZ += aZ;
		pX += vX;
		pY += vY;
		pZ += vZ;
	}
	
	uint64_t getDistance()
	{
		return abs(pX) + abs(pY) + abs(pZ);
	}
};

void parseInput(std::vector<Particle> &particles)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			Particle particle;
			size_t pos = 3;
			size_t endpos = line.find_first_of(",", pos);
			particle.pX = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of(",", pos);
			particle.pY = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of(">", pos);
			particle.pZ = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("<",endpos) + 1;
			endpos = line.find_first_of(",", pos);
			particle.vX = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of(",", pos);
			particle.vY = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of(">", pos);
			particle.vZ = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("<",endpos) + 1;
			endpos = line.find_first_of(",", pos);
			particle.aX = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of(",", pos);
			particle.aY = std::stoi(line.substr(pos, endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of(">", pos);
			particle.aZ = std::stoi(line.substr(pos, endpos-pos));
			
			particles.push_back(particle);
		}
	}
	input.close();
}

uint64_t findClosestParticle(std::vector<Particle> particles, bool collisions)
{
	uint64_t result = 0;
	uint64_t minDist = UINT64_MAX;
	
	for(int i=0; i<500; i++)
	{
		std::unordered_map<int64_t, unsigned int> cache;
		std::map<unsigned int, int> toRemove;
		for(unsigned int j=0; j<particles.size(); j++)
		{
			particles[j].update();
			if(collisions)
			{
				if(cache.count(particles[j].pX*1000000 + particles[j].pY*1000 + particles[j].pZ))
				{
					toRemove[j] = 1;
					toRemove[cache[particles[j].pX*1000000 + particles[j].pY*1000 + particles[j].pZ]] = 1;
				}
				else
				{
					cache[particles[j].pX*1000000 + particles[j].pY*1000 + particles[j].pZ] = j;
				}
			}
		}
		if(collisions)
		{
			for(auto it=toRemove.rbegin(); it!=toRemove.rend(); it++)
			{
				particles.erase(particles.begin()+it->first);
			}
		}
	}
	
	if(collisions)
	{
		result = particles.size();
	}
	else
	{
		for(unsigned int i=0; i<particles.size(); i++)
		{
			uint64_t newResult = particles[i].getDistance();
			if(newResult < minDist)
			{
				minDist = newResult;
				result = i;
			}
		}
	}

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<Particle> particles;
	
	parseInput(particles);
	
	resultA = findClosestParticle(particles, false);
	resultB = findClosestParticle(particles, true);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
