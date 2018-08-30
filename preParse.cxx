//      preParse.cxx
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


#include <fstream>

#include "preParse.hxx"

const short int INITIAL_TRIM = 6;

void preParse(std::string fileName)
{
	std::ifstream fileTxt("http.txt", std::ifstream::in);
	std::ofstream output("output_http.txt");
	std::string temp;

	while(fileTxt.good())
	{
		std::getline(fileTxt, temp);
		if(temp[0] == '|' && temp[1] == '0')
		{
			temp = temp.substr(INITIAL_TRIM, temp.size() - INITIAL_TRIM);
			for(std::string::iterator itr = temp.begin(); itr != temp.end(); itr++)
				if(*itr == '|')
					temp.erase(itr);

			output << temp << std::endl;
		}
	}
	fileTxt.close();
	output.close();
}
