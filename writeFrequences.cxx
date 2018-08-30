//      writeFrequences.cxx
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


#include <string>
#include <fstream>
#include <vector>
#include <map>
//#include <multimap>
#include <algorithm>

#include "keywordExtractor.hxx"
#include "multiEditDistance.hxx"
#include "keywordThreshold.hxx"
#include "writeFrequences.hxx"

//bool desc_ordering(std::pair<int, std::string>, std::pair<int, std::string>);

const short int THRESHOLD = 2;

//NOTA: GLI ITERATORI POSSONO ESSERE DEFINITI NEI CICLI FOR

void writeFrequences(std::vector<std::string> aligned, std::vector<std::string> fileParsed, std::string fileName, const float minKeywords)
{
	std::multimap<std::string, int> positionMap;
	std::map<std::string, std::map<int, int> > frequenceMap;
	std::map<std::string, std::map<int, int> >::iterator itrMap;
	std::map<int, int> appMap;
	std::map<int, int>::iterator itrItrMap;

	//RICORDARSI DI MODIFICARE QUESTO PERCHE' L'ESTRAZIONE DELLE FREQUENZE DALLE STRINGHE ALLINEATE NON SERVE PER RICAVARE IL PROTOCOLLO
	for(unsigned int i = 0;i<aligned.size();i++)
	{
		positionMap = keywordExtractor(aligned[i], THRESHOLD);//KeywordExtractor estrae le parole chiavi dalle stringhe
															//allineate che hanno lunghezza maggiore di threshold
		for(std::multimap<std::string, int>::iterator itrPos = positionMap.begin();itrPos != positionMap.end();itrPos++)
		{
			itrMap = frequenceMap.find(itrPos->first);
			if(itrMap != frequenceMap.end())
			{
				itrItrMap = itrMap->second.find(itrPos->second);
				if(itrItrMap != itrMap->second.end())
					itrItrMap->second++;
				else
					itrMap->second.insert(std::pair<int, int>(itrPos->second, 1));
			}
			else
			{
				appMap.insert(std::make_pair(itrPos->second, 1));
				frequenceMap.insert(std::make_pair(itrPos->first, appMap));
				appMap.clear();
			}
		}
	}

	//SEARCHING DELLE STRINGHE NEI PACCHETTI ORIGINALI E CONTEGGIO POSIZIONE E FREQUENZE
	std::map<std::string, std::map<int, int> > originalMarines;
	std::map<std::string, std::map<int, int> >::iterator itrMarines;
	std::map<int, int>::iterator itrItrMarines;

	for(unsigned int i = 0;i<fileParsed.size();i++)
	{
		for(unsigned int j = 0;j<fileParsed.at(i).size();j++)
		{
			for(itrMap = frequenceMap.begin(); itrMap != frequenceMap.end(); itrMap++)
			{
				if(fileParsed.at(i).substr(j, itrMap->first.size()) == itrMap->first)
				{
					itrMarines = originalMarines.find(itrMap->first);
					if(itrMarines != originalMarines.end())
					{
						itrItrMarines = itrMarines->second.find(j);
						if(itrItrMarines != itrMarines->second.end())
							itrItrMarines->second++;
						else
							itrMarines->second.insert(std::make_pair(j, 1));
					}
					else
					{
						appMap.insert(std::make_pair(j, 1));
						originalMarines.insert(std::make_pair(itrMap->first, appMap));
						appMap.clear();
					}
				}
			}
		}
	}

	//USARE IL NOME DEL FILE CHE SI PASSA COME PARAMETRO
	std::ofstream output("/home/roberto/Scrivania/httppcap_stats_one.txt");

	for(itrMarines = originalMarines.begin(); itrMarines != originalMarines.end(); itrMarines++)
	{
		output << itrMarines->first << " --- ";
		for(itrItrMarines = itrMarines->second.begin(); itrItrMarines != itrMarines->second.end(); itrItrMarines++)
			output << "Position: " << (itrItrMarines->first + 1) << " times: " << itrItrMarines->second << "; ";

		output << std::endl;
	}

	output.close();

	std::map<int, std::map<std::string, int> > positionFrequences;
	std::map<int, std::map<std::string, int> >::iterator itrPosFreq;
	std::map<std::string, int>::iterator itrItrPosFreq;
	std::map<std::string, int> appoggio;

	for(itrMarines = originalMarines.begin(); itrMarines != originalMarines.end(); itrMarines++)
	{
		for(itrItrMarines = itrMarines->second.begin(); itrItrMarines != itrMarines->second.end(); itrItrMarines++)
		{
			itrPosFreq = positionFrequences.find(itrItrMarines->first + 1);
			if(itrPosFreq != positionFrequences.end())
				itrPosFreq->second.insert(std::make_pair(itrMarines->first, itrItrMarines->second));
			else
			{
				appoggio.insert(std::make_pair(itrMarines->first, itrItrMarines->second));
				positionFrequences.insert(std::make_pair(itrItrMarines->first + 1, appoggio));
				appoggio.clear();
			}
		}
	}

	std::ofstream positionOutput("/home/roberto/Scrivania/httppcap_stats_two.txt");

	for(itrPosFreq = positionFrequences.begin(); itrPosFreq != positionFrequences.end(); itrPosFreq++)
	{
		positionOutput << itrPosFreq->first << "° - ";
		for(itrItrPosFreq = itrPosFreq->second.begin(); itrItrPosFreq != itrPosFreq->second.end(); itrItrPosFreq++)
			positionOutput << "Keyword: " << (itrItrPosFreq->first) << " times: " << itrItrPosFreq->second << "; ";

		positionOutput << std::endl;
	}

	positionOutput.close();

	std::map<int, std::map<std::string, int> >::iterator itrCluPosFreq;

	for(itrCluPosFreq = positionFrequences.begin(); itrCluPosFreq != positionFrequences.end();itrCluPosFreq++)
		itrCluPosFreq->second = multiEditDistance(itrCluPosFreq->second);

	for(itrCluPosFreq = positionFrequences.begin(); itrCluPosFreq != positionFrequences.end();itrCluPosFreq++)
		itrCluPosFreq->second = keywordThreshold(itrCluPosFreq->second);

	std::ofstream positionClusteredOutput("/home/roberto/Scrivania/httppcap_stats_three.txt");

	for(itrPosFreq = positionFrequences.begin(); itrPosFreq != positionFrequences.end(); itrPosFreq++)
	{
		positionClusteredOutput << itrPosFreq->first << "° - ";
		for(itrItrPosFreq = itrPosFreq->second.begin(); itrItrPosFreq != itrPosFreq->second.end(); itrItrPosFreq++)
			positionClusteredOutput << "Keyword: " << (itrItrPosFreq->first) << " times: " << itrItrPosFreq->second << "; ";

		positionClusteredOutput << std::endl;
	}

	positionClusteredOutput.close();
	
	std::map<int, std::multimap<int, std::string> > posFreqThreReordered;
	std::map<int, std::multimap<int, std::string> >::iterator itrThre;
	std::multimap<int, std::string>::iterator itrItrThre;
	
	for(itrPosFreq = positionFrequences.begin(); itrPosFreq != positionFrequences.end(); itrPosFreq++)
	{
		std::multimap<int, std::string> temp;
		
		for(itrItrPosFreq = itrPosFreq->second.begin(); itrItrPosFreq != itrPosFreq->second.end(); itrItrPosFreq++)
		{
			if(itrItrPosFreq->second > minKeywords)
				temp.insert(std::make_pair(itrItrPosFreq->second, itrItrPosFreq->first));
		}
		
		//std::sort(temp.begin(), temp.end(), desc_ordering);
		
		posFreqThreReordered.insert(std::make_pair(itrPosFreq->first, temp));
	}
	
	std::ofstream positionThreOutput("/home/roberto/Scrivania/httppcap_stats_four.txt");

	for(itrThre = posFreqThreReordered.begin(); itrThre != posFreqThreReordered.end(); itrThre++)
	{
		positionThreOutput << itrThre->first << "° - ";
		for(itrItrThre = itrThre->second.begin(); itrItrThre != itrThre->second.end(); itrItrThre++)
			positionThreOutput << "Keyword: " << (itrItrThre->second) << " times: " << itrItrThre->first << "; ";

		positionThreOutput << std::endl;
	}

	positionThreOutput.close();
}

//~ bool desc_ordering(std::pair<int, std::string> s1, std::pair<int, std::string> s2)
//~ {
	//~ return (s1.first > s2.first);
//~ }
