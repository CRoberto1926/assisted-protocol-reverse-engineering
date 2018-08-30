//      editDistance.cxx
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
#include <boost/numeric/ublas/matrix.hpp>

#include "similarityMatrixBuilder.hxx"
#include "editDistance.hxx"

//COSTRUISCE UNA COMPARE MATRIX IL CUI ELEMENTO IN BASSO A DESTRA E' LA DISTANZA DI EDIT FRA LE STRINGHE

int editDistance(std::string bufferOne, std::string bufferTwo)
{
	boost::numeric::ublas::matrix<int> similarityMatrix = similarityMatrixBuilder(keyword, 8, 1, 0);

	int numRowsCompare = bufferOne.size() +1;
	int numColumnsCompare = bufferTwo.size() + 1;

	boost::numeric::ublas::matrix<int> compareMatrix(numRowsCompare, numColumnsCompare);

	int gap = 0;

	for(int i=0;i<numRowsCompare;i++)
		compareMatrix(i, 0) = gap*i;

	for(int j=1;j<numColumnsCompare;j++)
		compareMatrix(0, j) = gap*j;

	int match;
	int del;
	int insert;

	for(int i=1;i<numRowsCompare;i++)
	{
		for(int j=1;j<numColumnsCompare;j++)
		{
			match = compareMatrix(i-1, j-1) + similarityMatrix(int(bufferOne[i-1]), int(bufferTwo[j-1]));
			del = compareMatrix(i-1, j) + gap;
			insert = compareMatrix(i, j-1) + gap;
			compareMatrix(i, j) = std::max(std::max(match, del), insert);
		}
	}

	return compareMatrix(numRowsCompare - 1, numColumnsCompare - 1);
}
