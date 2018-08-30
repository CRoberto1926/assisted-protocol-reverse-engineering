//      keywordThreshold.cxx
//      
//      Copyright 2011 Roberto Cortini <roberto dot cortini at gmail dot com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      


#include "keywordThreshold.hxx"

const double PERCENTAGE = 0.15;

std::map<std::string, int> keywordThreshold(std::map<std::string, int> keywordFrequences)
{
	int max = 0;

	for(std::map<std::string, int>::iterator itrKeyFreq = keywordFrequences.begin();itrKeyFreq != keywordFrequences.end();itrKeyFreq++)
		if(max < itrKeyFreq->second)
			max = itrKeyFreq->second;

	std::map<std::string, int>::iterator itrKeyFreq = keywordFrequences.begin();
	while(itrKeyFreq != keywordFrequences.end())
	{
		if(itrKeyFreq->second < max*PERCENTAGE)
			keywordFrequences.erase(itrKeyFreq++);
		else
			itrKeyFreq++;
	}


	return keywordFrequences;
}
