//      multiEditDistance.cxx
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


#include <map>
#include <cstdlib>

#include "editDistance.hxx"
#include "multiEditDistance.hxx"

const double PERCENTAGE = 0.15;

//CONTROLLA LA DISTANZA DI EDIT FRA 2 STRINGHE PER VEDERE SE SONO LA STESSA KEYWORD
//POI SOGLIA A SECONDA DI UNA DIFFERENZA PERCENTUALE
std::map<std::string, int> multiEditDistance(std::map<std::string, int> keywordFrequences)
{
	std::map<std::string, int>::iterator itrOneKeyFreq = keywordFrequences.begin();
	std::map<std::string, int>::iterator itrTwoKeyFreq = keywordFrequences.begin();
	itrTwoKeyFreq++;
	int score;
	int frequenceDifference;
	//int count;
	double mean;

	while(itrTwoKeyFreq != keywordFrequences.end())
	{
		//LA DISTANZA DI EDIT IN QUESTO CASO PARTICOLARE SARA' AL MASSIMO LA LUNGHEZZA DELLA STRINGA PIU' PICCOLA
		//PERCHE' STIAMO CONSIDERANDO CASI IN CUI UNA STRINGA E' INCLUSA NELL'ALTRA
		score = std::min(itrOneKeyFreq->first.size(), itrTwoKeyFreq->first.size());
		if(score == editDistance(itrOneKeyFreq->first, itrTwoKeyFreq->first))
		{
			frequenceDifference = abs(itrOneKeyFreq->second - itrTwoKeyFreq->second);
			mean = (itrOneKeyFreq->second + itrTwoKeyFreq->second)/2;
			if(frequenceDifference < mean*PERCENTAGE)
			{
				if(itrOneKeyFreq->first.size() < itrTwoKeyFreq->first.size())
				{
					keywordFrequences.erase(itrOneKeyFreq++);
					itrTwoKeyFreq++;
				}
				else
					keywordFrequences.erase(itrTwoKeyFreq++);
			}
			else
			{
				itrOneKeyFreq++;
				itrTwoKeyFreq++;
			}
		}
		else
		{
			itrOneKeyFreq++;
			itrTwoKeyFreq++;
		}
	}
	return keywordFrequences;
}
