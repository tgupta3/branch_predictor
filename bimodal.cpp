#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <bitset>
#include <math.h>
#include <algorithm>
#include <cstddef> 
#include <iterator>

using namespace std;

int size1; long long int size_table;
const int pc_size=6;

string hex2bin(string addre_hex)
{
	
	int addre_bin;
	istringstream st(addre_hex);
	st>>hex>>addre_bin;
	const int bit_length=pc_size*4;
	bitset<24> bits(addre_bin);
	
	string address_binary(bits.to_string());
	return address_binary;
	
}

string extract_index_bits(string addre_binary)
{
	//cout<<size<<endl;
	return addre_binary.substr((addre_binary.length()-2-size1),size1);


}

int bin2dec(string addre_binary)
{
	unsigned int value;
	//value=stoull(addre_binary,0,2);
	bitset<64> set(addre_binary);
	value=set.to_ulong();
	return value;
}


int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		cout<<"Incorrect arguments, Exiting"<<endl;
		return 0;
	}

	
			
			size1=atoi(argv[1]);
			size_table=pow(2,size1);
			vector<int> predict_table;
			predict_table.resize(size_table);
			//cout<<size_table<<endl;
			for(unsigned int i=0;i<size_table;i++) {
					predict_table[i]=2;
					}

			int mispredict_counter=0;
			int pre_input;
			ifstream trace_file(argv[5]);
			string linebuffer;
			string branch_status;
			string pc;
			int counter;
			int branch_index;
			string branch_predict;
			int num_prediction=0;
			string tex1 ="tushar";

			string tex(1,tex1[0]);
			while(trace_file && getline(trace_file, linebuffer))
			{
				if(linebuffer.length()==0) continue;
				branch_status=linebuffer.substr((linebuffer.length()-1));
				pc=linebuffer.substr(0,(linebuffer.length()-2));
				branch_index=bin2dec(extract_index_bits(hex2bin(pc)));
				num_prediction++;
				counter=predict_table[branch_index];
				//cout<<counter<<endl;
				//cout<<branch_index<<endl;
				if(counter>=2)
				{
					branch_predict='t';

				int ans1=branch_status.compare(tex);	
				if(ans1==0)
				{	
					if(counter<3)
					{
						predict_table[branch_index]++;
						
					}
					else
						predict_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						predict_table[branch_index]--;
					else
						predict_table[branch_index]=0;

				}
				}	
				else
				{
					branch_predict='n';
				
				int ans1=branch_status.compare(tex)	;

				if(ans1==0)
				{	
					if(counter<3)
					{
						predict_table[branch_index]++;
						
					}
					else
						predict_table[branch_index]=3;
				}
				else
				{
					if(counter>0)
						predict_table[branch_index]--;
					else
						predict_table[branch_index]=0;
					
				}
					
				}	
				
				int ans=branch_predict.compare(branch_status);

				if(ans!=0)

				{
						//cout<<"Mispredicted"<<endl;
						mispredict_counter++;
				}
				//cout<<predict_table[branch_index]<<endl;		

			}	
			//cout<<pc<<endl;

cout<<"COMMAND"<<endl;

			cout<<num_prediction<<endl;
			cout<<mispredict_counter<<endl;
for(unsigned int i=0;i<size_table;i++)
{
	cout<<i<<"  "<<predict_table[i]<<endl;

}

}