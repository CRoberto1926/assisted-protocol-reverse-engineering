//      pcapParser.cxx
//      
//      Copyright 2011 Roberto <roberto@roberto-MP061>
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


#include <pcap.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <algorithm>

bool extract(u_char, int);
u_char xorByte(u_char, u_char);

void pcapParser()
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct pcap_pkthdr header;
	const u_char *packet;
	
	handle = pcap_open_offline("/home/roberto/Scrivania/httpresponsepcap.pcap", errbuf);
	
	std::ofstream output("/home/roberto/Scrivania/httpresponse.txt");
	
	std::vector< std::vector<u_char> > packetsCollection;
	
	while((packet = pcap_next(handle, &header)) != NULL)
	{
		std::vector<u_char> packetBytes;
		for(int i = 0;i<std::max(header.len, header.caplen);i++)
		//for(int i = 42;i<45;i++)
		//for(int i = 66;i<std::max(header.len, header.caplen);i++)
		//for(int i = 54;i<std::max(header.len, header.caplen);i++)
		{
			packetBytes.push_back(packet[i]);
		}
		packetsCollection.push_back(packetBytes);
	}
	
	if(packetsCollection.size() < 2)
	{
		std::cout << "At least 2 packets are needed!" << std::endl;
		return;
	}
	
	for(std::vector< std::vector<u_char> >::iterator itrPacket = packetsCollection.begin();itrPacket != packetsCollection.end();itrPacket++)
	{
		
		for(std::vector<u_char>::iterator itrByte = (*itrPacket).begin();itrByte != (*itrPacket).end();itrByte++)
		{
			if(isprint((int)(*itrByte)))
				output << (*itrByte);
			//else/* if((int)(*itrByte) == 10)*/
			//	output << "CTRL" << (int)(*itrByte);
		}
		output << std::endl;
	}
	
	output.close();
	
	//~ std::vector<int> histogram(8, 0); 
	//~ 
	//~ for(std::vector< std::vector<u_char> >::iterator itrColNew = (packetsCollection.begin() + 1);itrColNew != packetsCollection.end();itrColNew++)
	//~ {
		//~ std::vector< std::vector<u_char> >::iterator itrColOld = itrColNew - 1;
		//~ 
		//~ int maxSize = std::max((*itrColOld).size(), (*itrColNew).size());
		//~ int minSize = std::min((*itrColOld).size(), (*itrColNew).size());
		//~ 
		//~ if(maxSize*8 > histogram.size()) histogram.resize(maxSize*8, 0);
		//~ 
		//~ int histCount = 0;
		//~ 
		//~ for(int i = 0;i<minSize;i++)
		//~ {
			//~ u_char xored = xorByte((*itrColOld).at(i), (*itrColNew).at(i));
			//~ for(int j = 0;j<8;j++)
			//~ {
				//~ histogram.at(histCount) += extract(xored, j);
				//~ histCount += 1;
			//~ }
		//~ }
	//~ }
	//~ 
	//~ for(std::vector<int>::iterator itrHist = histogram.begin();itrHist != histogram.end();itrHist++)
	//~ {
		//~ 
		//~ output << ((double)*itrHist / (double)packetsCollection.size())*100 << std::endl;
	//~ }
	//~ 
	//~ output.close();
}

bool extract(u_char data, int i) {
	bool returnValue = (data << i) & 0x80;
    return returnValue;
}

u_char xorByte(u_char byteOne, u_char byteTwo)
{
	u_char returnValue = byteOne^byteTwo;
	return returnValue;
}
