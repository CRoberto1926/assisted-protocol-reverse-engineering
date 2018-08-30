//      hex2bin.cxx
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

#include "hex2bin.hxx"

void hex2bin()
{
	std::ifstream hexFile("output_http.txt", std::ifstream::in);

	std::string appString;
	std::string bits;

	std::ofstream binFile("binary_http.txt");

	while(hexFile.good())
	{
		std::getline(hexFile, appString);
		for(unsigned int i = 0; i<appString.size(); i++)
		{
			if(appString[i] == '0')
				binFile << "0000";
			else if(appString[i] == '1')
				binFile << "0001";
			else if(appString[i] == '2')
				binFile << "0010";
			else if(appString[i] == '3')
				binFile << "0011";
			else if(appString[i] == '4')
				binFile << "0100";
			else if(appString[i] == '5')
				binFile << "0101";
			else if(appString[i] == '6')
				binFile << "0110";
			else if(appString[i] == '7')
				binFile << "0111";
			else if(appString[i] == '8')
				binFile << "1000";
			else if(appString[i] == '9')
				binFile << "1001";
			else if(appString[i] == 'a')
				binFile << "1010";
			else if(appString[i] == 'b')
				binFile << "1011";
			else if(appString[i] == 'c')
				binFile << "1100";
			else if(appString[i] == 'd')
				binFile << "1101";
			else if(appString[i] == 'e')
				binFile << "1110";
			else if(appString[i] == 'f')
				binFile << "1111";
		}
		binFile << std::endl;
	}

	hexFile.close();
	binFile.close();
}
