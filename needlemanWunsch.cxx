//      needlemanWunsch.cxx
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

#include "buildRegExp.hxx"
#include "similarityMatrixBuilder.hxx"
#include "needlemanWunsch.hxx"

std::string needlemanWunsch(std::string bufferOne, std::string bufferTwo)
{
	boost::numeric::ublas::matrix<int> similarityMatrix = similarityMatrixBuilder(counter, 8, 1, -1);

	int numRowsCompare = bufferOne.size() +1;
	int numColumnsCompare = bufferTwo.size() + 1;

	boost::numeric::ublas::matrix<int> compareMatrix(numRowsCompare, numColumnsCompare);

	int gap = 0; //PASSARLO COME PARAMETRO E ANCHE LA MATRICE VISTO CHE C'E' UNA FUNZIONE CHE LA COSTRUISCE

	for(int i=0;i<numRowsCompare;i++)
		compareMatrix(i, 0) = gap*i;

	for(int j=1;j<numColumnsCompare;j++)
		compareMatrix(0, j) = gap*j;

	int match;
	int del;
	int insert;

	//RIVEDERE L'USO DELLA SIMILARITY MATRIX PER USARNE DI "SPECIALIZZATE"
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

	int score, scoreDiag, scoreUp, scoreLeft;

	int i = numRowsCompare - 1;
	int j = numColumnsCompare - 1;

	std::string alignOne;
	std::string alignTwo;

	while(i>0 && j>0)
	{
		score = compareMatrix(i,j);
		scoreDiag = compareMatrix(i-1, j-1);
		scoreUp = compareMatrix(i-1, j);
		scoreLeft = compareMatrix(i, j-1);

		if(score == scoreDiag + similarityMatrix(int(bufferOne[i-1]), int(bufferTwo[j-1])))
		{
			alignOne.append(bufferOne.substr(--i, 1));
			alignTwo.append(bufferTwo.substr(--j, 1));
		}
		else if(score == (scoreLeft + gap))
		{
			alignOne.append("-");
			alignTwo.append(bufferTwo.substr(--j, 1));
		}
		else if(score == scoreUp + gap)
		{
			alignOne.append(bufferOne.substr(--i, 1));
			alignTwo.append("-");
		}
	}

	while(i>0)
	{
		alignOne.append(bufferOne.substr(--i, 1));
		alignTwo.append("-");
	}

	while(j>0)
	{
		alignOne.append("-");
		alignTwo.append(bufferTwo.substr(--j, 1));
	}

	char buffer;

	for(i=0;i<floor(alignOne.size()/2);i++)
	{
		buffer = alignOne[alignOne.size()-1-i];
		alignOne[alignOne.size()-1-i] = alignOne[i];
		alignOne[i] = buffer;
	}

	for(i=0;i<floor(alignTwo.size()/2);i++)
	{
		buffer = alignTwo[alignTwo.size()-1-i];
		alignTwo[alignTwo.size()-1-i] = alignTwo[i];
		alignTwo[i] = buffer;
	}

	std::string regExp = buildRegExp(alignOne, alignTwo);

	return regExp;
}
