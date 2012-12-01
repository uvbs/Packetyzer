/*
 *
 *  Copyright (C) 2012  Anwar Mohamed <anwarelmakrahy[at]gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to Anwar Mohamed
 *  anwarelmakrahy[at]gmail.com
 *
 */

#include "stdafx.h"
#include "cPacket.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	unsigned char buffer[] = { 
		0x00,0x1c,0xc0,0xe6,0xa2,0xab,0x00,0x24,0x2b,0x32,0xc3,0x55,0x08,0x00,
		0x45,0x00,0x00,0x34,0xc5,0x47,0x40,0x00,0x40,0x06,0x61,0x6a,0x0a,0x00,
		0x00,0x09,0x0a,0x00,0x00,0x0a,0x90,0x1b,0x0d,0x3d,0x15,0x94,0x78,0x2a,
		0x01,0xd5,0x41,0x7d,0x80,0x10,0x08,0xa5,0xd6,0x23,0x00,0x00,0x01,0x01,
		0x08,0x0a,0x00,0x34,0xb5,0x6d,0x00,0xe3,0x5e,0xf4 
	};

	cPacket Packetyzer;
	//Packetyzer.setFile(string("C:\\HTTP.cap"));
	//Packetyzer.setBuffer((char*)&buffer,sizeof(buffer));
	Packetyzer.setPCAPFile(string("C:\\sample.pcap"));

	cout << "Buffer loaded at: " << (DWORD*)Packetyzer.PCAPBaseAddress << endl;
	cout << "Buffer size: " << Packetyzer.PCAPSize << endl;

	//Packetyzer.ProcessPacket();
	Packetyzer.ProcessPCAP();

	for (unsigned int i=0; i < Packetyzer.nPCAPPackets; i++)
	{
		cout << i + 1 << "\t";
		if (Packetyzer.PCAPPacket[i].isIPPacket)
		{
			cout << "IP\t";
			if (Packetyzer.PCAPPacket[i].isTCPPacket)
			{
				cout << "TCP " << endl;
				cout << "TCPData\n";

				for(unsigned int j=0;j<Packetyzer.PCAPPacket[i].TCPDataSize;j++)
				{
					printf("%02x ",Packetyzer.PCAPPacket[i].TCPData[j]);
				}
			}
			else if (Packetyzer.PCAPPacket[i].isUDPPacket)
			{
				cout << "UDP " << Packetyzer.PCAPPacket[i].UDPDataSize << " " << ntohs(Packetyzer.PCAPPacket[i].UDPHeader.DatagramLength) << endl;
				cout << "UDPData\n";
			}
		}
		else if (Packetyzer.PCAPPacket[i].isARPPacket)
		{
			cout << "ARP" << endl;
		}
		else
		{
			cout << endl;
		}
	}

	system("PAUSE");
	return 0;
}

