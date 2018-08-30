//      datasetNW.cxx
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

 
#include <cstdlib>

#include "needlemanWunsch.hxx"
#include "datasetNW.hxx"

std::vector<std::string> datasetNW(std::vector<std::string> wordCollector)
{
	if((wordCollector.size() % 2) != 0) //GESTIRE ANCHE CASI DI WORDCOLLECTOR VUOTI
		wordCollector.pop_back();

	std::vector<std::string> nwResults;

	std::string temp;

	srand(time(NULL));

	for(unsigned int i=0;i<wordCollector.size();i++) //RANDOMIZZAZIONE NON SEMPRE NECESSARIA
		swap(wordCollector[i], wordCollector[rand() % wordCollector.size()]);

	for(unsigned int i = 1;i<wordCollector.size();i+=2)
		nwResults.push_back(needlemanWunsch(wordCollector[i-1], wordCollector[i]));

	return nwResults;
}
