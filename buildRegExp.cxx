//      buildRegExp.cxx
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


#include "buildRegExp.hxx"

std::string buildRegExp(std::string strOne, std::string strTwo)
{
	std::string regExp;

	for(unsigned int i=0;i<strOne.size();i++)
		(int(strOne[i]) == int(strTwo[i])) ? regExp.append(strOne.substr(i, 1)) : regExp.append("|");

	return regExp;
}
