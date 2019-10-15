#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

/*
What is a PCAPNG file?
Packet capture format that contains a "dump" of data packets captured over a network; saved in the PCAP Next Generation file format, a standard format for storing captured data.
*/

int main() {
	
	string protocolChoice;
	string value, sr_no,time,source,destination,info,protocol,len;
	int count,i, choice;

	while(true) {
	
		//The Program is re-reading the csv file in every iteration of the outer while loop
		ifstream file("packetsCaptured.csv");
		
		//It is starting from -1 because it will consider the heading "PROTOCOLS" as the zeroth packet
		count=-1;
		
		i=0;
		
		//Display Menu
		cout<<"\n\n***** PACKET ANALYZER *****\nEnter which protocol packets you want to see\n\t1) IP\n\t2) UDP\n\t3) TCP\n\t4) Ethernet\n\t5) ALL \n\t0) Exit\n\nChoice ? : ";
		
		//Accept the choice from the user
		cin>>choice;
		
		//Menu
		switch(choice){
			case 0:
				cout<<"\nSystem exited successfully...\n";
				file.close();
				return 0;
			case 1: 
				protocolChoice="ICMP";
				break;
			case 2: 
				protocolChoice="UDP";
				break;
			case 3: 
				protocolChoice="TCP";
				break;
			case 4:
				protocolChoice="ARP";
				break;
			case 5:
				protocolChoice="ALLPROTOCOLS";
				break;
			default:
				cout<<"\nInvalid Choice, Exiting Program...\n";
				return 1;
				
		}
		
		//Inner while loop to iterate through all the lines of the csv file, including the column labels
		while(file.good())
		{
			getline(file,sr_no,',');
			getline(file,time,',');
			getline(file,source,',');
			getline(file,destination,',');
			getline(file,protocol,',');
			getline(file,len,',');
			getline(file,info,'\n');

			protocol=string(protocol,1,protocol.length()-2);
			
			//protocol=="Protocol" is to check for the heading in the very beginning.
			//left sets the adjustfield format flag for the str stream to left.
			if(protocol=="Protocol"||protocol==protocolChoice||protocolChoice=="ALLPROTOCOLS")
			{
				cout <<	setw(4)	<<left	<<	i++;
				cout <<	setw(30)	<<left	<<	string( source, 1, source.length()-2 );
				cout <<	setw(30)	<<left	<<	string( destination, 1, destination.length()-2 );
				cout <<	setw(8)	<<left	<<	protocol;
				cout <<	setw(8)	<<left	<<	string( len, 1, len.length()-2 );
				cout <<	string( info, 1, info.length()-2 )<<"\n\n";
				count++;
			}
		}
		file.close();
		cout<<"\nTotal Packet Count: "<<count;
	}
	return 1;
}
