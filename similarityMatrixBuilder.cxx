//      similarityMatrixBuilder.cxx
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


#include "similarityMatrixBuilder.hxx"

boost::numeric::ublas::matrix<int> similarityMatrixBuilder(const fieldType ft, const short int bitsPerGroup, const short int similarityScore, const short int penaltyScore)
{
	int matrixDimension = pow(2, bitsPerGroup);
	boost::numeric::ublas::matrix<int> similarityMatrix(matrixDimension, matrixDimension);

	switch(ft)
	{
	case machineId:
	case communicationId:
	case address:
	case keyword:
	case protocolName:
	case protocolVersion:
	case packetClass:
	case reservedBits:
	case longPaddingBits:
	case counter:
	case checksum:
	case paddingBits:
		for(int i = 0;i<matrixDimension;i++)
			for(int j = 0;j<matrixDimension;j++)
				i == j ? similarityMatrix(i, j) = similarityScore : similarityMatrix(i, j) = 0;
		break;
	}
	return similarityMatrix;
}
