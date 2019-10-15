#include <bits/stdc++.h>
using namespace std;

// g++ -std=c++11 A2.cpp
// ./a.out

class Sender
{
	vector<bool> encoded_data;
	bool  *data;
	int data_size;
	int parity_bits;
	
	friend class Receiver;
	
	public:
	
	Sender(){data = NULL;}

	void getInput(int );
	
	void generateParity(int );
	
	void alterBit()
	{
		int pos;
		cout<<"Enter positon of bit to alter\n";
		cin>>pos;
		
		//If the index of the bit is valid, then compliment the bit
		if(encoded_data.size()>pos)
			encoded_data[pos] = ! encoded_data[pos];
		else
			cout<<"Invalid Position\n";
	}


	vector<bool> getBitset(){return encoded_data;}
	
	bool* getData(){return data;}

	void displayData(vector<bool> v)
	{
		cout<<setw(10)<<"Data : ";
		for( auto it = encoded_data.begin() + 1 ; it != encoded_data.end() ;it++ )
		{
			cout<<setw(5)<<*it;
		}
		cout<<"\n"<<setw(10)<<"Index : ";
		for(int i=1;i<encoded_data.size();i++)
		{
			cout<<setw(5)<<i;
		}
		cout<<"\n\n";
	}

	void displayData(bool v[])
	{
		cout<<setw(10)<<"Data : ";
		for( int i = 1 ; i<data_size ; i++ )
		{
			cout<<setw(5)<<v[i];
		}
		cout<<"\n"<<setw(10)<<"Index : ";
		for(int i=1;i<data_size;i++)
		{
			cout<<setw(5)<<i;
		}
		cout<<"\n\n";
	}
};

// i before e except after c
class Receiver
{
	vector<bool> encoded_data;
	bool *correct_data;
	int data_size;
	int parity_bits;
	
	//This boolean value is to signify that a sender has been received
	bool pass;

	public:
	Receiver(Sender &o)
	{
		this->encoded_data = o.encoded_data;
		this->data_size = o.data_size;
		this->parity_bits = o.parity_bits;
		pass = true;
	}


	void checkParity(int );

	//This function extracts the actual data from the encoded data
	//It discards the parity bits
	void extractData()
	{
		correct_data = new bool[data_size];
		for(int i = 0 , j = 0 , p = 0 ; i<encoded_data.size() ; i++)
		{
			if(i == pow(2,p))
				p += 1;
			else
			{
				correct_data[j] = encoded_data[i];
				j+=1;
			}
		}
	}


	vector<bool> getBitset(){return encoded_data;}
	bool* getcorrect_data(){return correct_data;}
	
	void displayData(vector<bool> v)
	{
		cout<<setw(10)<<"Data : ";
		for( auto it = encoded_data.begin() + 1 ; it != encoded_data.end() ;it++ )
		{
			cout<<setw(5)<<*it;
		}
		cout<<endl;
		cout<<setw(10)<<"Index : ";
		for(int i=1;i<encoded_data.size();i++)
		{
			cout<<setw(5)<<i;
		}
		cout<<"\n"<<endl;
	}

	void displayData(bool v[],int ipType)
	{
		int temp = 0;
		char temp1;
		string bin;
		switch(ipType)
		{
			case 1:
				for(int i = data_size -1 ,j=0 ;i > 0 ; i-- , j++)
				{
					temp += v[i]*pow(2,j);
				}
				cout<<"Received Data : "<<temp<<"\n"<<endl;
				break;

			case 2:
				for(int i = data_size -1 ,j=0 ;i > 0 ; i-- , j++)
				{
					temp += v[i]*pow(2,j);
				}
				bin = (char)temp;
				cout<<"Received Data : "<<bin<<"\n"<<endl;
				break;

			case 3:
				bin = "";
				for(int i=1 ; i < data_size ; i++)
				{
					bin += to_string(v[i]);
				}
				cout<<"Received Data : "<<bin<<"\n\n";
				break;
		}
	}

};

//1 : Integer		2 : Character		3 : bitString
void Sender :: getInput(int ch)
{
	int temp;
	int r;
	char temp1;
	string bin;
	switch(ch)
	{
		case 1:
			cout<<"\n\nEnter Input (Integer): ";
			cin>>temp;
			cout<<endl;

			while(temp!=0)
			{
				r = temp%2;
				temp /= 2;
				encoded_data.push_back(r);
			}
			reverse(encoded_data.begin(),encoded_data.end());
			break;

		case 2:
			cout<<"\n\nEnter Input (Character): ";
			cin>>temp1;
			cout<<endl;
			
			temp = int(temp1);
			bin = bitset<7>(temp).to_string();
			for(auto it = bin.begin();it!=bin.end();it++)
			{
				encoded_data.push_back(*it-48);
			}
			break;

		case 3:
			cout<<"\n\nEnter Input (bit String): ";
			cin>>bin;
			cout<<endl;

			for(auto it = bin.begin();it!=bin.end();it++)
			{
				encoded_data.push_back(*it - 48);
			}
			break;
	}

	encoded_data.insert(encoded_data.begin(),NULL);
	
	data_size = encoded_data.size();
	data = new bool[data_size];
	copy(encoded_data.begin(),encoded_data.end(),data);

	int p = 0;
	for( int i = 0 ; i < 10 ; i++ )
	{
		if( pow(2,i) >= (data_size + i ) )
		{	
			p = i;
			break;
		}
	}
	parity_bits = p;
	for(int i = 0 ; i < p ; i++)
	{
		int t = pow(2,i);
		encoded_data.insert(encoded_data.begin() + t , NULL);
	}
	cout<<"Entered Data : \n"<<endl;
	displayData(data);
}


void Sender :: generateParity(int x)							
{
	for(int i = 0;i<parity_bits;i++)
	{
		bool fl;
		if(x == 0)
			fl = false;
		else if(x == 1)
			fl = true;
		int t = pow(2,i);
		cout<<"Parity : "<<t<<"\tpos : ";
		string str = "";
		for(int j = t + 1 ; j<encoded_data.size() ; j++)
		{
			if( t&j )
			{
				//cout<<" "<<j;
				str = str + " " +  to_string(j);
				if(encoded_data[j] == 1)
					fl = !fl; 
			}
		}
		cout<<setw(20)<<str;
		cout<<"\tbit : "<<fl<<endl<<endl;
		encoded_data[t] = fl;
	}
}


void Receiver :: checkParity(int x)
{
	vector <bool> st;
	for(int i = 0;i<parity_bits;i++)
	{
		bool fl;
		if(x == 0)
			fl = false;
		else if(x == 1)
			fl = true;
		int t = pow(2,i);
		cout<<"Parity : "<<t<<"\tpos : ";
		string str = "";
		for(int j = t ; j<encoded_data.size() ; j++)
		{
			if( t&j )
			{
				//cout<<" "<<j;
				str = str + ' ' + to_string(j);
				if(encoded_data[j] == 1)
					fl = !fl; 
			}
		}
		cout<<setw(20)<<str;
		cout<<"\tbit : "<<fl<<endl<<endl;
		st.push_back(fl);
		if(fl != 0)
		{
			pass = false;
		}
	}
	int pos = 0;
	for(int i = 0 ; i < st.size() ;i++ )
	{
		if(st[i] == 1)	
		{
			pos += pow(2,i);
		}
	}
	if(!pass)
	{
		cout<<"Error Detected \n Position : "<<pos<<endl<<endl;
		encoded_data[pos] = !encoded_data[pos];
		cout<<"Corrected Error\n"<<endl;
	}
	else
	{
		cout<<"Hamming pass\n"<<endl;
	}
}


int main()
{
	int ipType;

	Sender ob;
	
	
	cout<<"-------------------------------------Sender Side----------------------------------------\n\n";
	
	cout<<"-----------------Input----------------\n";
	cout<<"\nEnter Input type : \n\t1 : Integer		\n\t2 : Character		\n\t3 : bitString\n > ";
	cin>>ipType;
	cout<<endl;
	ob.getInput(ipType);
	
	cout<<"-------Calculating Parity Bits--------\n\n";
	// x = 0 even parity     x = 1 odd parity
	ob.generateParity(1);		
	ob.displayData(ob.getBitset());
	
	cout<<"-------------Transmission-------------\n\n";
	char ch;
	cout<<"Alter Data ? y/n : ";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		ob.alterBit();
	
	cout<<"---------------Data Sent--------------\n\n";
	ob.displayData(ob.getBitset());
	
	cout<<"Transmission Complete\n\n";
	
	
	
	cout<<"------------------------------------Receiver Side----------------------------------------\n\n";
	
	cout<<"-------------Received data------------\n\n";
	Receiver r(ob);
	r.displayData(r.getBitset());
	
	// x = 0 even parity     x = 1 odd parity
	cout<<"-------------checking Parity----------\n\n";
	r.checkParity(1);			
	
	cout<<"-------------received Data------------\n\n";
	r.extractData();
	r.displayData(r.getcorrect_data(),ipType);
	
}
