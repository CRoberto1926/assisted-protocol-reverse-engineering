//      pdc.cxx
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


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>

void pdc()
{
	std::ifstream inFile("/home/roberto/Scrivania/binary_skype52613bis_udp_histogram.txt", std::ifstream::in);
	std::string temp;
	std::vector<double> histogram;
	char * ctemp;
	
	if(inFile.is_open())
	{
		while(inFile.good())
		{
			std::getline(inFile, temp);
			ctemp = new char [temp.size()+1];
			strcpy(ctemp, temp.c_str());
			histogram.push_back(strtod(ctemp, NULL));
			delete[] ctemp;
		}
		
		inFile.close();
	}
	else
	{
		std::cout << "Error opening file";
	}
	
	std::vector<int> quantizedHistogram;
	
	for(std::vector<double>::iterator itr = histogram.begin();itr < histogram.end();itr++)
	{
		int quantPerc = 0;
		bool quantized = false;
		
		while(!quantized)
		{
			if(abs(*itr - quantPerc) <= 5) //Attenzione ai bordi (ad esempio se si quantizza a intorno 5 e il valore è 2.5, si manda in zero o in 5?)
			{
				quantizedHistogram.push_back(quantPerc);
				quantized = true;
			}
			
			quantPerc += 10;
		}
	}
	
	std::ofstream output("/home/roberto/Scrivania/binary_skype52613bis_udp_histogram_quant.txt");
	
	for(std::vector<int>::iterator itr = quantizedHistogram.begin();itr < quantizedHistogram.end();itr++)
	{
		
		output << *itr << std::endl;
	}
	
	output.close();
}
