//      keywordExtractor.cxx
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


#include "keywordExtractor.hxx"

const char UNMATCH_CHAR = '|';

std::multimap<std::string, int> keywordExtractor(std::string aligned, const short unsigned int threshold)
{
	std::multimap<std::string, int> positionMap;
	std::string keyword;
	bool lastUnmatch = false;

	for(unsigned int i=0; i<aligned.size();i++)
	{
		if(aligned.at(i) != UNMATCH_CHAR)
		{
			keyword.push_back(aligned.at(i));
			lastUnmatch = false;
		}
		else if((!lastUnmatch) && (aligned.at(i) == UNMATCH_CHAR))
		{
			lastUnmatch = true;

			if(keyword.size() > threshold/* && keyword.size() < 40*/) //AGGIUNTA A MANO QUI; CORREGGERE
				positionMap.insert(std::pair<std::string, int>(keyword, i + 1 - keyword.size()));

			keyword.clear();
		}
	}
	return positionMap;
}
