//      parseTxt.cxx
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

#include "parseTxt.hxx"

const short int NEWLINE_ASCII = 10;
const short int NEWLINE_REPEATS = 1;

//RISCRIVERE CON GETLINE

std::vector<std::string> parseTxt(std::string fileName)
{
	std::vector<std::string> packets;
	//DEVE FUNZIONARE CON LA STRINGA PASSATA
	std::ifstream fileTxt("/home/roberto/Scrivania/httpNOctrlchar.txt", std::ifstream::in);
	std::string packet;
	char partialPacket;
	short int newlines_sequence = 0;

	while(fileTxt.good())
	{
		partialPacket = fileTxt.get();
		packet.push_back(partialPacket);

		if(partialPacket == NEWLINE_ASCII)
		{
			if(++newlines_sequence == NEWLINE_REPEATS)
			{
				packets.push_back(packet);
				packet.clear();
				newlines_sequence = 0;
			}
		}
		else
			newlines_sequence = 0;
	}
	fileTxt.close();

	return packets;
}
