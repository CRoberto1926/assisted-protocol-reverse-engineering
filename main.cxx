//      main.cxx
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


//IMPLEMENTARE KMP PER STRING MATCHING

#include "datasetNW.hxx"
#include "parseTxt.hxx"
//~ #include "preParse.hxx"
#include "writeFrequences.hxx"
//~ #include "hex2bin.hxx"

#include <vector>
#include <string>
#include <fstream>

#include "pcapParser.hxx"
#include "pdc.hxx"

int main(int argc, char **argv)
{
//~ hex2bin(); //Routine adesso inutile che convertiva un file di testo da esadecimale a binario
			//In particolare ripuliva i file che uscivano dalla routine sottostante preParse
//~ 
//~ preParse("http.txt"); //Routine di preparsing che serviva a ripulire i file in modo da avere solo le stringhe protocollare
						//Veniva usato perché prima facevamo uscire da Wireshark file in formato K12 text file
//~ 
//~ std::string fileName = "output_dns3k.txt";
 std::vector<std::string> fileParsed = parseTxt("/home/roberto/Scrivania/httpNOctrlchar.txt"); //Prende un file di testo con un pacchetto per riga e crea
					//un vettore di stringhe protocollari
//~ 
//~ //PULIRE LE STRINGHE ALLINEATE PER I PASSAGGI SUCCESSIVI PERCHE' I GAP VENGONO PRESI COME CARATTERI
 std::vector<std::string> aligned = datasetNW(fileParsed); //Esegue NW su tutto il dataset randomizzandolo
//~ //aligned = datasetNW(aligned);
//~ //aligned = datasetNW(aligned);
//~ //aligned = datasetNW(aligned);
//~ //aligned = datasetNW(aligned);
 writeFrequences(aligned, fileParsed, "/home/roberto/Scrivania/httppcap_stats_four.txt", fileParsed.size()*0.002);
//~ 
	std::ofstream alignedTxt("/home/roberto/Scrivania/httppcap_aligned.txt");
	for(std::vector<std::string>::iterator itr = aligned.begin(); itr != aligned.end(); itr++)
		alignedTxt << *itr << std::endl;

	alignedTxt.close();
	
	//pcapParser();
	
	//pdc();
	
	return 0;
}
